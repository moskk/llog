#ifndef LLOG_HPP
#define LLOG_HPP

#include "llog_sinks.hpp"
#include "llog_record.hpp"
#include "llog_utils.hpp"

namespace llog
{

template <class sink_t, class... sinks> class logger
{
public:
    typedef record<logger<sink_t,sinks...>> record_t;
    typedef logger<sinks...> next_logger_t;

    logger(sink_t& sink, sinks&... next_sinks)
        :m_sink(sink), m_next_logger(next_sinks...){}

    record_t&& operator()(level lvl = level(bad))
    {
        if(lvl.good())
        {
            return std::move(record_t(*this, lvl));
        }
        else
        {
            return std::move(record_t(*this, log_level));
        }
    }

    void put(const record_t& r)
    {
        if(
                (r.log_level.good() && m_sink.log_level(r.log_level))
                ||
                m_sink.log_level(log_level))
        {
            m_sink.put(r);
        }
    }

    level log_level;

private:
    sink_t& m_sink;
    next_logger_t m_next_logger;
};

template <class sink_t> class logger<sink_t>
{
public:
    typedef record<logger<sink_t>> record_t;

    logger(sink_t& sink):m_sink(sink){}

    record_t&& operator()(level lvl = level(bad))
    {
        if(lvl.good())
        {
            return std::move(record_t(*this, lvl));
        }
        else
        {
            return std::move(record_t(*this, log_level));
        }
    }

    void put(const record_t& r)
    {
        if(
                (r.log_level.good() && m_sink.log_level(r.log_level))
                ||
                m_sink.log_level(log_level))
        {
            m_sink.put(r);
        }
    }

    level log_level;

private:
    sink_t& m_sink;
};

}

#endif // LLOG_HPP

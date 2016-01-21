#ifndef LLOG_HPP
#define LLOG_HPP

#include "llog_sinks.hpp"
#include "llog_record.hpp"
#include "llog_utils.hpp"

namespace llog
{

template<class writer_t, class record_t>
record_t&& make_record(writer_t& writer, loglevel lvl)
{
    if(log_level_mask(lvl).good())
    {
        return std::move(record_t(writer, lvl));
    }
    else
    {
        return std::move(record_t(writer, writer.log_level()));
    }
}

template <class sink_t, class... sinks> class sink_writer
{
public:
    typedef record<sink_writer<sink_t,sinks...>> record_t;
    typedef sink_writer<sinks...> next_writer_t;
    sink_writer(sink_t& sink, sinks&... next_sinks)
        :m_sink(sink), m_next_writer(next_sinks...){}

    inline record_t&& operator()(loglevel lvl = bad)
    {
        return make_record<sink_writer, record_t>(*this, lvl);
    }

    inline void put(const std::stringstream& record, loglevel lvl)
    {
        // если при создании записи был указан тип сообщения
        if(log_level_mask(lvl).good())
        {
            // и если при этом данный тип пролезает
            // в приёмник по маске типов сообщений
            if(sink().level_mask(lvl))
            {
                // сохраняем
                sink().put(record);
                m_next_writer.put(record, lvl);
            }
        }
        // если же для записи не был указан особый тип,
        // проверяем маску типов логгера
        else if(sink().level_mask(log_level()))
        {
            sink().put(record);
            m_next_writer.put(record, lvl);
        }
    }

    inline loglevel log_level(){return m_next_writer.log_level();}

    inline sink_t& sink(){return m_sink;}

private:
    sink_t& m_sink;
    next_writer_t m_next_writer;
};

template <class sink_t> class sink_writer<sink_t>
{
public:
    typedef record<sink_writer<sink_t>> record_t;

    sink_writer(sink_t& sink):m_sink(sink){}

    inline record_t&& operator()(log_level_mask lvl = log_level_mask(bad))
    {
        return make_record<sink_writer, record_t>(*this, lvl);
    }

    inline void put(const std::stringstream& record, loglevel lvl)
    {
        // если при создании записи был указан тип сообщения
        if(log_level_mask(lvl).good())
        {
            // и если при этом данный тип пролезает
            // в приёмник по маске типов сообщений
            if(sink().level_mask(lvl))
            {
                // сохраняем
                sink().put(record);
            }
        }
        // если же для записи не был указан особый тип,
        // проверяем маску типов логгера
        else if(sink().level_mask(log_level()))
        {
            sink().put(record);
        }
    }


    inline loglevel log_level(){return m_log_level;}

    inline sink_t& sink(){return m_sink;}

private:
    sink_t& m_sink;
    loglevel m_log_level;
};

template<class sink_t, class... sinks> class logger :
        public sink_writer<sink_t, sinks...>
{
public:

};

}

#endif // LLOG_HPP

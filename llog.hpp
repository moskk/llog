#ifndef LLOG_HPP
#define LLOG_HPP

#include <iomanip>
#include "llog_sinks.hpp"
#include "llog_record.hpp"
#include "llog_utils.hpp"

namespace llog
{

template<class writer_t, class record_t>
record_t make_record(writer_t* writer, loglevel lvl, const ctxinfo& ctx_info)
{
    if(lvl != bad)
    {
        return std::move(record_t(writer, lvl, ctx_info));
    }
    else
    {
        return std::move(record_t(writer, writer->log_level(), ctx_info));
    }
}

template <class sink_t, class... sinks> class sink_writer
{
public:
    typedef record<sink_writer<sink_t,sinks...>> record_t;
    typedef sink_writer<sinks...> next_writer_t;
    sink_writer(sink_t& sink, sinks&... next_sinks)
        :m_sink(sink), m_next_writer(next_sinks...){}

    inline record_t&& operator()(loglevel lvl = bad, const ctxinfo& ctx_info = ctxinfo())
    {
        return make_record<sink_writer, record_t>(*this, lvl, ctx_info);
    }

    inline void put(const std::stringstream& record, loglevel lvl)
    {
        if( log_level_mask(log_level())(none) || sink().level_mask(none) || log_level_mask(lvl)(none) )
        {
            return;
        }
        if(lvl != bad)
        {
            if(sink().level_mask(lvl))
            {
                sink().put(record);
                m_next_writer.put(record, lvl);
            }
            return;
        }
        if(sink().level_mask(log_level()))
        {
            sink().put(record);
            m_next_writer.put(record, lvl);
            return;
        }
    }

    inline loglevel& log_level(){return m_next_writer.log_level();}

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

    inline record_t&& operator()(loglevel lvl = bad, const ctxinfo& ctx_info = ctxinfo())
    {
        return make_record<sink_writer, record_t>(*this, lvl, ctx_info);
    }

    inline void put(const std::stringstream& record, loglevel lvl)
    {
        // если на уровне логера, приёмника или записи логирование отключено
        // путём выбора соответствующего уровня (none)
        if( log_level_mask(log_level())(none) || sink().level_mask(none) || log_level_mask(lvl)(none) )
        {
            // игнорируем запись
            return;
        }
        // если при создании записи был указан уровень сообщения
        if(lvl != bad)
        {
            // и если при этом данный уровень пролезает
            // в приёмник по маске уровней сообщений
            if(sink().level_mask(lvl))
            {
                // сохраняем
                sink().put(record);
            }
        }
        // если же для записи не был указан особый уровень,
        // проверяем маску уровней логгера
        else if(sink().level_mask(log_level()))
        {
            sink().put(record);
        }
    }

    inline loglevel& log_level(){return m_log_level;}

    inline sink_t& sink(){return m_sink;}

private:
    sink_t& m_sink;
    loglevel m_log_level = warn;
};

template<class sink_t, class... sinks> class logger :
        public sink_writer<sink_t, sinks...>
{
    typedef sink_writer<sink_t, sinks...> base;
public:
    logger(options o, sink_t& sink, sinks&... sinks_)
        :base(sink, sinks_...), opts(o){}

    typedef record<base> record_t;

    inline record_t operator()(loglevel lvl, const ctxinfo &ctx_info = ctxinfo())
    {
        return std::move(get_record(lvl, ctx_info));
    }

    inline record_t operator()(const ctxinfo &ctx_info, loglevel lvl = bad)
    {
        return std::move(get_record(lvl, ctx_info));
    }

    inline record_t operator()()
    {
        return std::move(get_record(bad, ctxinfo()));
    }

private:
    inline record_t get_record(loglevel lvl, const ctxinfo &ctx_info)
    {
        record_t rec(make_record<base, record_t>(this, lvl, ctx_info));
        if(opts(log_date_time))
        {
            using namespace std::chrono;
            time_t now(system_clock::to_time_t(system_clock::now()));
            rec << '[' << std::put_time(std::localtime(&now), "%F %T") << "] ";
        }
        if(opts(log_loglevel))
        {
            rec << '[' << loglevel_to_str(rec.log_level()) << "] ";
        }
        if(opts(log_ctxinfo) && rec.ctx_info().good())
        {
            rec << '[' << rec.ctx_info().file << ':' << rec.ctx_info().line << "] ";
        }
        return std::move(rec);
    }

private:
    options opts;
};

}

#endif // LLOG_HPP

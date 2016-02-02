#ifndef LLOG_RECORD_HPP
#define LLOG_RECORD_HPP

#include <sstream>
#include "llog_utils.hpp"
#include "llog_ctxinfo.hpp"

namespace llog
{

template <class writer_t> class record : public std::stringstream
{
    typedef std::stringstream base;
public:
    record(writer_t *writer, loglevel lvl, const ctxinfo& ctx_info)
        :base(), m_writer(writer), m_log_level(lvl), m_ctx(ctx_info){}

    record(record&&other):base(), m_writer(0), m_log_level(loglevel::invalid)
    {
        swap(static_cast<base&>(other));
        std::swap(m_writer, other.m_writer);
        other.m_writer = nullptr;
        std::swap(m_log_level, other.m_log_level);
        std::swap(m_ctx, other.m_ctx);
    }

    ~record()
    {
        if( m_log_level == none )
        {
            return;
        }
        if( m_writer && (tellp() != 0) )
        {
            *this << std::endl;
            m_writer->put(static_cast<const std::stringstream&>(*this), log_level());
        }
    }
    loglevel log_level() const {return m_log_level;}
    const ctxinfo& ctx_info() const {return m_ctx;}
private:
    writer_t* m_writer = nullptr;
    loglevel m_log_level = invalid;
    ctxinfo m_ctx;
};

}

#endif // LLOG_RECORD_HPP

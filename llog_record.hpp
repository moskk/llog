#ifndef LLOG_RECORD_HPP
#define LLOG_RECORD_HPP

#include <sstream>
#include "llog_utils.hpp"

namespace llog
{

template <class writer_t> class record : public std::stringstream
{
public:
    record(writer_t &writer, loglevel lvl):m_writer(writer), m_log_level(lvl){}
    record(record&&) = default;
    ~record(){m_writer.put(static_cast<const std::stringstream&>(*this), log_level());}
    loglevel log_level() const {return m_log_level;}
private:
    writer_t &m_writer;
    loglevel m_log_level;
};

}

#endif // LLOG_RECORD_HPP

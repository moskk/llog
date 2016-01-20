#ifndef LLOG_RECORD_HPP
#define LLOG_RECORD_HPP

#include <sstream>
#include "llog_utils.hpp"

namespace llog
{

template <class logger_t> class record : public std::stringstream
{
public:
    //using std::stringstream::operator<<;
    record(logger_t &logger, level lvl):m_logger(logger), log_level(lvl){}
    record(record&&) = default;
    ~record(){m_logger.put(*this);}
    level log_level;

private:
    logger_t &m_logger;
};

}

#endif // LLOG_RECORD_HPP

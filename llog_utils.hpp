#ifndef LLOG_UTILS_HPP
#define LLOG_UTILS_HPP

#include <string>
#include "llog_bit_mask.hpp"

namespace llog
{

enum class thread_mode{unsafe, safe};

enum class exception_mode{_throw = 1, no_throw = 0};

typedef unsigned char loglevel_t;

enum loglevel:loglevel_t
{
    bad = 0x0,
    debug = 0x1,
    info = 0x2,
    warn = 0x4,
    error = 0x8,
    fatal = 0x10,
    all = debug | info | warn | error | fatal,
    none = 0x20                               // не логировать
};

std::string loglevel_to_str(loglevel ll);

typedef bit_mask<loglevel_t, loglevel, all> log_level_mask;

typedef unsigned char log_options_t;

enum option : log_options_t
{
    default_ = 0x0,
    log_date_time = 0x1,
    log_ctxinfo = 0x2,
    log_loglevel = 0x4
};

typedef bit_mask<log_options_t, option, default_> options;

} // namespace llog

#endif // LLOG_UTILS_HPP

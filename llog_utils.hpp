#ifndef LLOG_UTILS_HPP
#define LLOG_UTILS_HPP

#include <string>
#include "llog_bit_mask.hpp"

namespace llog
{

// режим потокобезопасности для приёмников
enum class thread_mode{unsafe, safe};

// режим работы с исключениями для приёмников
enum class exception_mode{_throw = 1, no_throw = 0};

typedef unsigned char loglevel_t;

// значения уровней логирования
enum loglevel:loglevel_t
{
    invalid = 0x0,                            // для записей (использовать уровень логера по умолчанию)
    debug = 0x1,
    info = 0x2,
    warn = 0x4,
    error = 0x8,
    fatal = 0x10,
    all = debug | info | warn | error | fatal,
    none = 0x20                               // не логировать
};

std::string loglevel_to_str(loglevel ll);

// контейнер допустимых уровней логирования
typedef bit_mask<loglevel_t, loglevel, all> log_level_mask;

typedef unsigned char log_options_t;

enum option : log_options_t
{
    log_default = 0x0,  // только сообщения
    log_date_time = 0x1,// логировать дату/время
    log_ctxinfo = 0x2,  // логировать файл и номер строки (см. пример использования)
    log_loglevel = 0x4  // логировать уровень сообщения
};

typedef bit_mask<log_options_t, option, invalid> options;

} // namespace llog

#endif // LLOG_UTILS_HPP

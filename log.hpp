#ifndef LOG_HPP
#define LOG_HPP

#include "llog.hpp"

using namespace llog;

extern sink::stdout<thread_mode::unsafe, exception_mode::no_throw> so_sink;

extern sink::stdout<thread_mode::safe, exception_mode::no_throw> ts_so_sink;

// незащищённый логер, выводящий в стандартный вывод и в файл
extern logger<sink::file<thread_mode::unsafe, exception_mode::no_throw>,
sink::stdout<thread_mode::unsafe, exception_mode::no_throw>> unsafe_log;

// потокобезопасный логер, выводящий в стандартный вывод и в файл
extern logger<sink::file<thread_mode::safe, exception_mode::no_throw>,
sink::stdout<thread_mode::safe, exception_mode::no_throw>> safe_log;

extern logger<sink::file<thread_mode::unsafe, exception_mode::_throw>> bad_logger;

#endif // LOG_HPP

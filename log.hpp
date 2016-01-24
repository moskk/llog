#ifndef LOG_HPP
#define LOG_HPP

#include "llog.hpp"

using namespace llog;

// незащищённый логер, выводящий в стандартный вывод и в файл
extern logger<sink::file<thread_mode::unsafe, exception_mode::no_throw>,
sink::stdout<thread_mode::unsafe, exception_mode::no_throw>> unsafe_log;
// потокобезопасный логер, выводящий в стандартный вывод и в файл
extern logger<sink::file<thread_mode::safe, exception_mode::no_throw>,
sink::stdout<thread_mode::safe, exception_mode::no_throw>> safe_log;

#endif // LOG_HPP

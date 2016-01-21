#ifndef LOG_HPP
#define LOG_HPP

#include "llog.hpp"

using namespace llog;

// незащищённый логер, выводящий в стандартный вывод и в файл
extern sink_writer<sink::file<thread_mode::unsafe>, sink::stdout<thread_mode::unsafe>> unsafe_log;

// потокобезоавсный логер, выводящий в стандартный вывод и в файл
extern sink_writer<sink::file<thread_mode::safe>, sink::stdout<thread_mode::safe>> safe_log;

#endif // LOG_HPP

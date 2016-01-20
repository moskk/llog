#ifndef LOG_HPP
#define LOG_HPP

#include "llog.hpp"
extern llog::logger<llog::sink::file<llog::mode::unsafe>,
llog::sink::file<llog::mode::thread_safe>> log1;
#endif // LOG_HPP


#include "log.hpp"
#include "llog_utils.hpp"

using namespace llog;

// незащищённый файловый приёмник для сообщений всех уровней
sink::file<thread_mode::unsafe, exception_mode::no_throw>
f_sink(log_level_mask(all), "log.txt");

// потокобезопасный файловый приёмник для сообщений всех уровней
sink::file<thread_mode::safe, exception_mode::no_throw>
ts_f_sink(log_level_mask(), "tslog.txt");
// в сконструированном по умолчанию объекте log_level_mask включены все уровни

// незащищённый приёмник потока стандартного вывода
// принимает сообщения всех уровней, кроме debug и warn
sink::stdout<thread_mode::unsafe, exception_mode::no_throw>
so_sink(log_level_mask(all) - debug - info);

// потокобезопасный приёмник потока стандартного вывода
// принимает сообщения всех уровней, кроме debug и fatal
sink::stdout<thread_mode::safe, exception_mode::no_throw>
ts_so_sink(log_level_mask(all) - debug - info);

// незащищённый логер, выводящий в стандартный вывод и в файл
logger<sink::file<thread_mode::unsafe, exception_mode::no_throw>,
sink::stdout<thread_mode::unsafe, exception_mode::no_throw>>
unsafe_log(options() + log_date_time + log_ctxinfo + log_loglevel, f_sink, so_sink);

// потокобезоавсный логер, выводящий в стандартный вывод и в файл
logger<sink::file<thread_mode::safe, exception_mode::no_throw>,
sink::stdout<thread_mode::safe, exception_mode::no_throw>>
safe_log(options() + log_date_time + log_ctxinfo + log_loglevel, ts_f_sink, ts_so_sink);

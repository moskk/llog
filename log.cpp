
#include "log.hpp"
#include "llog_utils.hpp"

using namespace llog;

log_level_mask all_mask;

// незащищённый файловый приёмник
sink::file<thread_mode::unsafe, exception_mode::no_throw> f_sink("log.txt");

// потокобезопасный файловый приёмник
sink::file<thread_mode::safe, exception_mode::no_throw> ts_f_sink("tslog.txt");

// незащищённый приёмник потока стандартного вывода
sink::stdout<thread_mode::unsafe, exception_mode::no_throw>
so_sink(all_mask);

// потокобезопасный приёмник потока стандартного вывода
sink::stdout<thread_mode::safe, exception_mode::no_throw>
ts_so_sink(all_mask);

// незащищённый логер, выводящий в стандартный вывод и в файл
logger<sink::file<thread_mode::unsafe, exception_mode::no_throw>,
sink::stdout<thread_mode::unsafe, exception_mode::no_throw>>
unsafe_log(options() + log_date_time + log_ctxinfo, f_sink, so_sink);

// потокобезоавсный логер, выводящий в стандартный вывод и в файл
logger<sink::file<thread_mode::safe, exception_mode::no_throw>,
sink::stdout<thread_mode::safe, exception_mode::no_throw>>
safe_log(options() + log_date_time + log_ctxinfo, ts_f_sink, ts_so_sink);

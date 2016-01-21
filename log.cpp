
#include "log.hpp"
#include "llog_utils.hpp"

using namespace llog;

// незащищённый файловый приёмник
sink::file<thread_mode::unsafe> f_sink("log.txt");

// потокобезопасный файловый приёмник
sink::file<thread_mode::safe> ts_f_sink("tslog.txt");

// незащищённый приёмник потока стандартного вывода
sink::stdout<thread_mode::unsafe> so_sink;

// потокобезопасный приёмник потока стандартного вывода
sink::stdout<thread_mode::safe> ts_so_sink;

// незащищённый логер, выводящий в стандартный вывод и в файл
sink_writer<sink::file<thread_mode::unsafe>, sink::stdout<thread_mode::unsafe>> unsafe_log(f_sink, so_sink);

// потокобезоавсный логер, выводящий в стандартный вывод и в файл
sink_writer<sink::file<thread_mode::safe>, sink::stdout<thread_mode::safe>> safe_log(ts_f_sink, ts_so_sink);

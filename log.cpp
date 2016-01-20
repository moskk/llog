
#include "log.hpp"
#include "llog_utils.hpp"

using namespace llog;

// незащищённый файловый приёмник
sink::file<mode::unsafe> fsink("log.txt");

// потокобезопасный файловый приёмник
sink::file<mode::thread_safe> tsfsink("tslog.txt");

//

logger<sink::file<mode::unsafe>, sink::file<mode::thread_safe>> log1(fsink, tsfsink);


#include "llog_utils.hpp"

std::string llog::loglevel_to_str(llog::loglevel ll)
{
    switch (ll) {
    case debug:
        return "debug";
    case info:
        return "info ";
    case warn:
        return "warn ";
    case error:
        return "error";
    case fatal:
        return "fatal";
    default:
        return "";
    }
}

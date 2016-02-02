
#include "llog_utils.hpp"

std::string llog::loglevel_to_str(llog::loglevel ll)
{
    switch (ll) {
    case debug:
        return "DEBUG";
    case info:
        return "INFO ";
    case warn:
        return "WARN ";
    case error:
        return "ERROR";
    case fatal:
        return "FATAL";
    case all:
        return " ALL ";
    default:
        return "     ";
    }
}

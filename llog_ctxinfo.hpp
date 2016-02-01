#ifndef LLOG_CTXINFO_HPP
#define LLOG_CTXINFO_HPP

namespace llog
{

struct ctxinfo
{
    const char * file;
    unsigned int line;

    ctxinfo(const char * f = nullptr, unsigned int l = 0):file(f),line(l){}
    ctxinfo(const ctxinfo&) = default;
    bool good() const {return file && line;}
};

}

#define CTXINFO llog::ctxinfo(__FILE__, __LINE__)

#endif // LLOG_CTXINFO_HPP

#ifndef LLOG_UTILS_HPP
#define LLOG_UTILS_HPP

namespace llog
{

enum class mode{unsafe, thread_safe};

typedef unsigned char loglevel_t;

enum loglevel:loglevel_t{bad = 0, debug = 0x1, info = 0x2, warn = 0x4,
                         error = 0x8, fatal = 0x10, none = 0x20};

class level
{
public:
    level(){}
    level(loglevel l):ll(l){}
    inline level& operator = (const level& r){ll = r.ll;return *this;}
    inline level& operator << (const level& l){ll |= l.ll;return *this;}
    inline level& operator >> (const level& l){ll &= !l.ll;return *this;}
    inline bool operator () (const level& l) const {return ll&l.ll;}
    inline bool good() const {return ll;}
private:
    loglevel_t ll = debug | info | warn | error | fatal;
};

} // namespace llog

#endif // LLOG_UTILS_HPP

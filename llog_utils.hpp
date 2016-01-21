#ifndef LLOG_UTILS_HPP
#define LLOG_UTILS_HPP

namespace llog
{

enum class thread_mode{unsafe, safe};

enum class exception_mode{_throw = 1, no_throw = 0};

typedef unsigned char loglevel_t;

enum loglevel:loglevel_t{bad = 0,
                         debug = 0x1,
                         info = 0x2,
                         warn = 0x4,
                         error = 0x8,
                         fatal = 0x10,
                         all = debug | info | warn | error | fatal,
                         none = 0x20};

class log_level_mask
{
public:
    log_level_mask(){}
    log_level_mask(loglevel l):ll(l){}
    inline log_level_mask& operator = (const log_level_mask& r){ll = r.ll;return *this;}
    inline log_level_mask& operator = (const loglevel& l){ll = l;return *this;}
    inline log_level_mask& operator << (const log_level_mask& l){ll |= l.ll;return *this;}
    inline log_level_mask& operator >> (const log_level_mask& l){ll &= !l.ll;return *this;}
    inline bool operator () (const log_level_mask& l) const {return ll&l.ll;}
    inline bool operator () (loglevel l) const {return ll&l;}
    inline bool good() const {return ll;}
private:
    //loglevel_t ll = debug | info | warn | error | fatal;
    loglevel_t ll = 0;
};

} // namespace llog

#endif // LLOG_UTILS_HPP

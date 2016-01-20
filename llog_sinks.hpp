#ifndef LLOG_SINKS_HPP
#define LLOG_SINKS_HPP

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <mutex>
#include "llog_utils.hpp"
#include "llog_record.hpp"

namespace llog
{

namespace sink
{

template <mode m> class file;

template<> class file<mode::unsafe>
{
public:
    file(const std::string& f):m_f(f){}
    void put(const std::stringstream& ss) const
    {
        using namespace std;
        ofstream f(m_f, ofstream::out|ofstream::ate);
        f.exceptions(ofstream::failbit|ofstream::badbit);
        f << ss.str();
    }
    level log_level;

private:
    std::string m_f;
};

template<> class file<mode::thread_safe> : file<mode::unsafe>
{
public:
    typedef file<mode::unsafe> base;
    file(const std::string& f):base(f), m_f(f){}
    void put(const std::stringstream& ss) const
    {
        using namespace std;
        lock_guard<mutex> _(m_mut);
        base::put(ss);
    }
private:
    std::string m_f;
    mutable std::mutex m_mut;
};

template <mode m> class stdout;

template <> class stdout<mode::unsafe>
{
public:
    void put(const std::stringstream& ss) const
    {
        std::cout << ss.str();
    }

    level log_level;
};

template <> class stdout<mode::thread_safe> : stdout<mode::unsafe>
{
public:
    typedef stdout<mode::unsafe> base;
    void put(const std::stringstream& ss) const
    {
        using namespace std;
        lock_guard<mutex> _(m_mut);
        base::put(ss);
    }
private:
    mutable std::mutex m_mut;
};

} // namespace sink

} // namespace llog

#endif // LLOG_SINKS_HPP

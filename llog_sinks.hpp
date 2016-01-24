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

template <thread_mode threadm, exception_mode excptm/* = exception_mode::no_throw*/> class file;

template<exception_mode excptm> class file<thread_mode::unsafe, excptm>
{
public:
    file(const std::string& f):m_f(f){}
    void put(const std::stringstream& ss) const
    {
        using namespace std;
        try
        {
            ofstream f(m_f, ofstream::out|ofstream::ate);
            f.exceptions(ofstream::failbit|ofstream::badbit);
            f << ss.str();
        }
        catch(...)
        {
            if((bool)excptm)
            {
                throw current_exception();
            }
        }
    }

    log_level_mask level_mask;

protected:
    std::string m_f;
};

template<exception_mode excptm> class file<thread_mode::safe, excptm>
        : file<thread_mode::unsafe, excptm>
{
public:
    typedef file<thread_mode::unsafe, excptm> base;
    file(const std::string& f):base(f){}
    void put(const std::stringstream& ss) const
    {
        using namespace std;
        volatile lock_guard<mutex> _(m_mut);
        base::put(ss);
    }

    using base::level_mask;

private:
    mutable std::mutex m_mut;
};

template <thread_mode threadm, exception_mode excptm = exception_mode::no_throw> class stdout;

template <exception_mode excptm> class stdout<thread_mode::unsafe, excptm>
{
public:
    stdout(const log_level_mask& llm):level_mask(llm){}
    void put(const std::stringstream& ss) const
    {
        std::cout << ss.str();
    }

    log_level_mask level_mask;
};

template <exception_mode excptm> class stdout<thread_mode::safe, excptm>
        : stdout<thread_mode::unsafe, excptm>
{
public:
    typedef stdout<thread_mode::unsafe, excptm> base;
    stdout(const log_level_mask& llm):base(llm){}
    void put(const std::stringstream& ss) const
    {
        using namespace std;
        try
        {
            volatile lock_guard<mutex> _(m_mut);
            base::put(ss);
        }
        catch(...)
        {
            if((bool)excptm)
            {
                throw current_exception();
            }
        }
    }

    using base::level_mask;

private:
    mutable std::mutex m_mut;
};

} // namespace sink

} // namespace llog

#endif // LLOG_SINKS_HPP

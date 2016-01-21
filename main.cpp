#include <iostream>

using namespace std;

#include "log.hpp"

int main(int argc, char *argv[])
{
    std::string s("Hello llog!");
    int i(1);
    float f(.3);
    double d(5.2);
    unsafe_log() << s << " int " << i << " float " << f << " double " << d << "\n";
    safe_log() << s << " int " << i << " float " << f << " double " << d << "\n";
    return 0;
}

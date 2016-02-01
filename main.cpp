#include <iostream>

using namespace std;

#include "log.hpp"

int main(int argc, char *argv[])
{
    try
    {
        {
            std::string s("Hello llog!");
            int i(1);
            float f(.3);
            double d(5.2);
            // т.к. record - наследник stringstream, поддерживается вывод основных типов.
            unsafe_log() << s << " int " << i << " float " << f << " double " << d;
            safe_log() << s << " int " << i << " float " << f << " double " << d;
        }

        {
            // к сожалению, полностью прозрачной для пользователя возможности вывода
            // информации о контексте реализовать не получилось, только вот так:
            unsafe_log(CTXINFO) << " <--- some trouble here";
            safe_log(CTXINFO) << " <--- some trouble here";
        }

        {
            // уровни логирования проверяются на в приёмниках, что позволяет
            // более гибко управлять процессом. например, в файл писать более подробный лог
            // для дальнейшего анализа, а в стандартный вывод выводить только основные
            // события. уровень логера по умолчанию - warn, но для каждой записи можно
            // указать свой уровень.
            // как вариант, можно создать несколько логгеров, использующих одни и теже
            // приёмники и отличающихся только уровнем по умолчанию. кроме того, можно
            // на ходу менять уровень логгера по умолчанию.
            unsafe_log(llog::error, CTXINFO) << " some trouble happened";
            safe_log(CTXINFO, llog::info) << " but we could miss them "
                                             "when looking in stdout";
            // в данном случае второе сообщение не пройдёт в приёмники станд. вывода.
        }

        {
            // можно на ходу менять уровень логера по умолчанию
            unsafe_log.log_level() = error;
            // следующие записи в данный логгер будут иметь указанный уровень.
            unsafe_log() << "i am an error now";
        }
    }
    catch(const std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}

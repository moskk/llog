#include <iostream>
#include <vector>
#include <thread>

using namespace std;

#include "log.hpp"

int main(int argc, char *argv[])
{
    try
    {
        {
            // вызов оператора "скобки" для логера возвращает объект записи,
            // в деструкторе которого и происходит запись в приёмник, поэтому
            // конкретный момент записи зависит от выбранного уровня оптимизации
            // кода. чтобы избежать этого, можно использовать логер в отдельном блоке
            unsafe_log();
            // в приёмники попадают только непустые записи (эта не попадёт)
        }

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
            // следующие записи в данный логгер будут по умолчанию
            // иметь указанный уровень.
            unsafe_log.log_level() = error;
            unsafe_log() << "i am an error now";
            safe_log.log_level() = info;
            safe_log() << "info message";
        }

        // приёмники могут быть простыми или потокозащищёнными. корректное
        // поведение простых приёмников в потоках без потокозащиты не гарантируется,
        // т.к. файловые и строковые потоки стандартной библиотеки, используемые
        // при реализации логера, непотокобезопасны
        vector<thread> vt;
        for(int i = 0; i < 20; ++i)
        {
            vt.push_back(move(thread([]()
            {
                safe_log() << "my id is " << this_thread::get_id() << " and i am ok";
                unsafe_log() << "i am " << this_thread::get_id() << " and i am a bad idea";
            }
            )));
        }
        for(auto& t : vt)
        {
            t.join();
        }

        {
            // также на ходу можно менять маски уровней приёмников
            so_sink.level_mask = log_level_mask(all);
            ts_so_sink.level_mask = so_sink.level_mask;
            // теперь в стандартный вывод попадают все записи
            unsafe_log() << "I'M EVERYWHERE NOW!";
            safe_log() << "YES, WE ARE!!!";
        }
    }
    catch(const std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}

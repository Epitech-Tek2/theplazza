/*
** Epitech project, tek2.
** Clement-Muth, jonathan-Cohen && Sarah-Keppler
** Plazza
*/

#ifndef PLAZZA_MYLIB_HPP
#define PLAZZA_MYLIB_HPP

#include <vector>
#include <string>

namespace MyLib
{
    class MyLib
    {
    public:
        MyLib() = default;
        MyLib(MyLib const &other) = delete;
        ~MyLib() = default;

        MyLib &operator=(MyLib const &other) = delete;

        static std::vector<std::string> msplit(std::string const &s, std::string const &delim);
    };
}

#endif

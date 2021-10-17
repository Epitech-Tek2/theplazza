/*
** Epitech project, tek2.
** Clement-Muth, jonathan-Cohen && Sarah-Keppler
** Plazza
*/

#include <algorithm>
#include <iostream>
#include "MyLib.hpp"

std::vector<std::string> MyLib::MyLib::msplit(std::string const &s, std::string const &delim)
{
    std::vector<std::string> v{};
    size_t last{0}, next{0};
    while ((next = s.find(delim, last)) != std::string::npos) {
        v.emplace_back(s.substr(last, next-last));
        last = next + delim.size();
    }
    v.emplace_back(s.substr(last));
    return v;
}

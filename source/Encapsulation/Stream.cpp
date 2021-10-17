/*
** EPITECH PROJECT, 2021
** threadpool
** File description:
** Stream
*/

#include "Stream.hpp"

enc::Mutex safe::Stream::_mutexPrint{};

Code Color::getCode(void) const noexcept
{
    return (_code);
}

std::ostream& operator<<(std::ostream& os, const Color& color) {
    if (color.getCode() == DEFAULT)
        return (os << "\033[0;0m");
    return os << "\033[01;38;5;" << color.getCode() << "m";
}

safe::Stream::~Stream()
{
    enc::UniqueLock lock(_mutexPrint);
    std::cout << this->str();
}

/*
** Epitech Project, tek2.
** Sarah-Keppler
** Plazza
*/

#include "Exceptions.hpp"

Plazza::Exception::Exception(std::string const &message) noexcept : _message(message){}

const char *Plazza::Exception::what() const noexcept
{
    return _message.c_str();
}

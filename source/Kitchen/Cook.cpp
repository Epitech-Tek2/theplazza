/*
** EPITECH PROJECT, 2021
** B-CCP-400-STG-4-1-theplazza-clement.muth
** File description:
** Cook
*/

#include "Cook.hpp"

Plazza::Cook::Cook() noexcept
 : _cook(false),
   _pizza()
{}

void Plazza::Cook::cook(Pizza const pizza) noexcept
{
    _pizza = pizza;
    _cook = true;
    _begin = std::chrono::high_resolution_clock::now();
}

void Plazza::Cook::endCook(void) noexcept
{
    _cook = false;
}

std::string Plazza::Cook::displayStatus(void) noexcept
{
    std::stringstream s;
    double elapse = 0;

    if (_cook) {
        _actual = std::chrono::high_resolution_clock::now();
        elapse = std::chrono::duration_cast<std::chrono::milliseconds>(_actual - _begin).count() / 1000.0;
        s << std::setprecision(2) << std::fixed;
        s << "cook a " << _pizza.unpack() << " (" << elapse << "/" << _pizza.getTime().count() / 1000.0 << "s)" << std::endl;
    } else
        s << "is waiting..." << std::endl;
    return (s.str());
}

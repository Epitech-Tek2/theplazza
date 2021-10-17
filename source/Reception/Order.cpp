/*
** Epitech project, tek2.
** Clement-Muth, jonathan-Cohen && Sarah-Keppler
** Plazza
*/

#include <iostream>
#include <algorithm>
#include <regex>
#include "Order.hpp"
#include "MyLib.hpp"
#include "Exceptions.hpp"

Plazza::Order::Order(std::string const &s, double const factor) : _nbrPizzaInOrder{0}
{
    std::vector<std::string> orders{MyLib::MyLib::msplit(s, "; ")};
    for (std::vector<std::string>::const_iterator it = orders.cbegin(), et = orders.cend(); et != it; ++it) {
        if (2 != std::count((*it).cbegin(), (*it).cend(), ' '))
            throw MinorException{"Unknown command: " + *it + ". help for more informations."};
        std::vector<std::string> parts{MyLib::MyLib::msplit(*it, " ")};
        int i{Plazza::Pizza::getType(parts[0])};
        if (84 == i)
            throw MinorException{"Unknown pizza type: " + parts[0] + "."};
        PizzaType type{(PizzaType)i};
        i = Plazza::Pizza::getSize(parts[1]);
        if (84 == i)
            throw MinorException{"Unknown pizza size: " + parts[1] + "."};
        PizzaSize size{(PizzaSize)i};
        if (!std::regex_match(parts[2], std::regex{"x[1-9][0-9]*"}))
            throw MinorException{"Incorrect number: " + parts[2] + "."};
        Pizza pizza{type, size, factor};
        _pizzas.emplace_back(pizza);
        _nbrmax.emplace_back(std::stoi(parts[2].substr(1)));
        _nbrdone.emplace_back(0);
        _isBeingBaked.emplace_back(false);
        _nbrPizzaInOrder += _nbrmax.back();
    }
}
/*
Plazza::Order::Order(Pizza const &pizza, int const nbr) noexcept
{
    _pizzas.emplace_back(pizza);
    _nbrmax.emplace_back(nbr);
    _nbrdone.emplace_back(0);
    _isBeingBaked.emplace_back(false);
}

Plazza::Order::Order(std::vector<Pizza> const &pizzas, std::vector<int> const &nbrs) noexcept : _pizzas{pizzas}, _nbrmax{nbrs}
{
    for (int i = 0, e = _pizzas.size(); e > i; ++i) {
        _nbrdone.emplace_back(0);
        _isBeingBaked.emplace_back(false);
    }
}*/

std::vector<std::string> Plazza::Order::getNoteForKitchens(void) const noexcept
{
    std::vector<std::string> notes;

    for (std::size_t i = 0; i < _pizzas.size(); ++i) {
        for (int e = 0; e < _nbrmax[i]; ++e) {
            notes.push_back(_pizzas[i].pack());
        }
    }
    return (notes);
}

bool Plazza::Order::iscompleted() noexcept
{
    for (int i = 0, e = _nbrmax.size(); e > i; ++i) {
        _nbrPizzaInOrder -= _nbrmax[i];
        if (_nbrmax[i] != _nbrdone[i])
            return false;
    }
    return true;
}

int Plazza::Order::getNbrPizza(void) const noexcept
{
    return (_nbrPizzaInOrder);
}

bool Plazza::Order::update(Pizza const &pizza) noexcept
{
    for (std::size_t e = 0; e < _pizzas.size(); ++e) {
        if (
            pizza.getType() == _pizzas[e].getType()
            && pizza.getSize() == _pizzas[e].getSize()
            && _nbrdone[e] < _nbrmax[e]
        ) {
            ++_nbrdone[e];
            return (true);
        }
    }
    return (false);
}

void Plazza::Order::displayStatus() const noexcept
{
    for (std::size_t it = 0, et = _pizzas.size(); et > it; ++it) {
        std::cout << "    " << _pizzas[it].unpack()
        << "  (" << _nbrdone[it] << "/" << _nbrmax[it] << ")" << std::endl;
    }
}

std::string Plazza::Order::log() const noexcept
{
    std::time_t time = std::time(nullptr);
    std::stringstream s;
    std::string stime = std::asctime(std::localtime(&time));
    size_t end = stime.find_last_of('\n');

    if (end != std::string::npos)
        stime = stime.substr(0, end);
    s << "[" << stime << "] Order ";
    for (std::size_t it = 0, et = _pizzas.size(); et > it; ++it) {
        s << std::to_string(_nbrmax[it]) << " " << _pizzas[it].getTypeS() << " size " << _pizzas[it].getSizeS();
        if (it + 2 == et)
            s << " and ";
        else if (it + 1 < et)
            s << ", ";
    }
    s << ".";
    return (s.str());
}

std::ofstream& operator<<(std::ofstream &out, Plazza::Order const &order)
{
    out << order.log().c_str() << std::endl;
    return out;
}

/*
** EPITECH PROJECT, 2021
** threadpool
** File description:
** Stock
*/

#include "Stock.hpp"

const std::map<Plazza::Ingredient, std::string> ingredientRef = {
    {Plazza::DOE, "Doe"},
    {Plazza::TOMATO, "Tomato"},
    {Plazza::GRUYERE, "Gruyere"},
    {Plazza::HAM, "Ham"},
    {Plazza::MUSHROOMS, "Mushrooms"},
    {Plazza::STEAK, "Steak"},
    {Plazza::EGGPLANT, "Eggplant"},
    {Plazza::GOAT_CHEESE, "Goat cheese"},
    {Plazza::CHIEF_LOVE, "Chief love"}
};

Plazza::Stock::Stock(std::size_t const regeneration) noexcept
: _stop(false), _regeneration(std::chrono::milliseconds(regeneration))
{
    _stock[DOE] = 5;
    _stock[TOMATO] = 5;
    _stock[GRUYERE] = 5;
    _stock[HAM] = 5;
    _stock[MUSHROOMS] = 5;
    _stock[STEAK] = 5;
    _stock[EGGPLANT] = 5;
    _stock[GOAT_CHEESE] = 5;
    _stock[CHIEF_LOVE] = 5;
}

bool Plazza::Stock::canCook(Pizza const &pizza)
{
    enc::UniqueLock lock(_mstock);
    std::vector<Ingredient> ingredients = pizza.getIngredients();

    for (std::vector<Ingredient>::const_iterator i = ingredients.begin(); i != ingredients.end(); ++i) {
        if (!_stock.at(*i))
            return (false);
    }
    for (std::vector<Ingredient>::const_iterator i = ingredients.begin(); i != ingredients.end(); ++i) {
        _stock.at(*i) -= 1;
    }
    return (true);
}

bool Plazza::Stock::generate(void)
{
    enc::UniqueLock lock(_mstock);

    _cvstock.wait_for(lock, _regeneration, [this]{return (this->_stop);});
    if (_stop) {
        return (false);
    }
    for (std::map<Ingredient, std::size_t>::iterator i = _stock.begin(); i != _stock.end(); ++i) {
        ++i->second;
    }
    return (true);
}

std::string Plazza::Stock::displayStatus(void)
{
    enc::UniqueLock lock(_mstock);
    std::stringstream s;

    s << "    Available stock: (regenerate after " << std::setprecision(2) << std::fixed << (_regeneration.count() / 1000.0) << "s)" << std::endl;
    for (std::map<Ingredient, std::size_t>::iterator i = _stock.begin(); i != _stock.end(); ++i)
        s << "        " << ingredientRef.at(i->first) << ": " << i->second << std::endl;
    s << std::endl;
    return (s.str());
}

void Plazza::Stock::stop(void)
{
    enc::UniqueLock lock(_mstock);

    _stop = true;
    _cvstock.notify_all();
}

/*
** Epitech project, tek2.
** Clement-Muth, jonathan-Cohen && Sarah-Keppler
** Plazza
*/

#include "Pizza.hpp"

const std::unordered_map<Plazza::PizzaType, Plazza::pizza> pizzaRef = {
    {Plazza::PizzaType::Margarita, {"Margarita", Plazza::margarita, 1}},
    {Plazza::PizzaType::Regina, {"Regina", Plazza::regina, 2}},
    {Plazza::PizzaType::Americana, {"Americana", Plazza::americana, 2}},
    {Plazza::PizzaType::Fantasia, {"Fantasia", Plazza::fantasia, 4}}
};

const std::unordered_map<Plazza::PizzaSize, std::string> sizeRef = {
    {Plazza::PizzaSize::S, "S"},
    {Plazza::PizzaSize::M, "M"},
    {Plazza::PizzaSize::L, "L"},
    {Plazza::PizzaSize::XL, "XL"},
    {Plazza::PizzaSize::XXL, "XXL"},
};

Plazza::Pizza::Pizza(std::string const s, double const multiplier)
{
    int pos = s.find(':');

    if (!std::regex_match(s, std::regex{"([0-9]+):([0-9]+)"}))
        throw MinorException("Pizza: invalid pizza");
    _type = static_cast<PizzaType>(std::stoi(s.substr(0, pos)));
    _size = static_cast<PizzaSize>(std::stoi(s.substr(pos + 1)));
    _ingredients = pizzaRef.at(_type)._ingredients;
    _time = std::chrono::milliseconds((int)(pizzaRef.at(_type)._time * multiplier * 1000));
    _pack = s;
    _unpack = pizzaRef.at(_type)._name + " " + sizeRef.at(_size);
}

Plazza::Pizza::Pizza(PizzaType const type, PizzaSize const size, double const multiplier) noexcept : _type{type}, _size{size}
{
    _type = type;
    _size = size;
    _time = std::chrono::milliseconds((int)(pizzaRef.at(_type)._time * multiplier * 1000));
    _ingredients = pizzaRef.at(_type)._ingredients;
    _pack = std::to_string((int)_type) + ":" + std::to_string((int)_size);
    _unpack = pizzaRef.at(_type)._name + " " + sizeRef.at(_size);
}

Plazza::Pizza::Pizza(const Pizza &other) noexcept
 :
 _time{other._time},
 _type{other._type},
 _size{other._size},
 _pack{other._pack},
 _unpack{other._unpack},
 _ingredients{other._ingredients}
{}

Plazza::Pizza &Plazza::Pizza::operator=(Pizza const &other) noexcept
{
    _type = other._type;
    _size = other._size;
    _time = other._time;
    _pack = other._pack;
    _unpack = other._unpack;
    _ingredients = other._ingredients;
    return *this;
}

Plazza::Pizza &Plazza::Pizza::operator>>(std::string &s) noexcept
{
    s.append(getTypeS());
    s.append(" ");
    s.append(getSizeS());
    return *this;
}

std::chrono::milliseconds Plazza::Pizza::getTime(void) const noexcept
{
    return (_time);
}

std::string Plazza::Pizza::getCommandPack(void) const noexcept
{
    return (_pack);
}

std::string Plazza::Pizza::getCommandUnpack(void) const noexcept
{
    return (_unpack);
}

std::vector<Plazza::Ingredient> Plazza::Pizza::getIngredients(void) const noexcept
{
    return (_ingredients);
}

Plazza::PizzaType Plazza::Pizza::getType() const noexcept
{
    return (_type);
}

int Plazza::Pizza::getType(std::string const &s)
{
    if (!std::regex_match(s, std::regex{"[a-z]+"}))
        return (84);
    std::array<std::string, 4> types{"regina", "margarita", "americana", "fantasia"};
    std::size_t idx{84}, i{1};
    for (std::array<std::string, 4>::const_iterator it = types.cbegin(), et = types.cend(); et != it; ++it) {
        if(!(*it).compare(s))
            idx = i;
        i *= 2;
    }
    return (idx);
}

std::string Plazza::Pizza::getTypeS() const noexcept
{
    std::array<std::string, 4> types{"regina", "margarita", "americana", "fantasia"};
    PizzaType ref[4] = {PizzaType::Regina, PizzaType::Margarita, PizzaType::Americana, PizzaType::Fantasia};
    for (int it = 0; 4 > it; ++it)
        if (ref[it] == _type)
            return types[it];
    return std::string{};
}

Plazza::PizzaSize Plazza::Pizza::getSize() const noexcept
{
    return (_size);
}

int Plazza::Pizza::getSize(std::string const &s)
{
    if (!std::regex_match(s, std::regex{"S|M|L|XL|XXL"}))
        return (84);
    std::array<std::string, 5> sizes{"S", "M", "L", "XL", "XXL"};
    std::size_t idx{84}, i{1};
    for (std::array<std::string, 5>::const_iterator it = sizes.cbegin(), et = sizes.cend(); et != it; ++it) {
        if(!(*it).compare(s))
            idx = i;
        i *= 2;
    }
    return (idx);
}

std::string Plazza::Pizza::getSizeS() const noexcept
{
    std::array<std::string, 5> sizes{"S", "M", "L", "XL", "XXL"};
    PizzaSize refs[5] = {PizzaSize::S, PizzaSize::M, PizzaSize::L, PizzaSize::XL, PizzaSize::XXL};
    for (int it = 0; 5 > it; ++it)
        if (refs[it] == _size)
            return sizes[it];
    return std::string{};
}

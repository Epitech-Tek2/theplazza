/*
** EPITECH PROJECT, 2021
** threadpool
** File description:
** Pizza
*/

#ifndef PIZZA_HPP_
#define PIZZA_HPP_

#include <regex>
#include <array>
#include <unordered_map>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <chrono>

#include "Plazza.hh"
#include "Pizza.hpp"
#include "Exceptions.hpp"

namespace Plazza {
    struct pizza
    {
        pizza(std::string const &name, std::vector<Ingredient> const &ingredient, int time)
        : _name(name),
          _ingredients(ingredient),
          _time(time)
        {};

        std::string _name;
        std::vector<Ingredient> _ingredients;
        int _time;
    };

    class Pizza
    {
        public:
            Pizza() = default;
            Pizza(std::string const s, double const multiplier);
            Pizza(PizzaType const type, PizzaSize const size, double const multiplier) noexcept;
            ~Pizza() = default;
            Pizza(const Pizza &other) noexcept;

            Pizza &operator=(Pizza const &other) noexcept;
            Pizza &operator>>(std::string &s) noexcept;

            std::chrono::milliseconds getTime(void) const noexcept;
            std::string getCommandPack(void) const noexcept;
            std::string getCommandUnpack(void) const noexcept;
            std::vector<Ingredient> getIngredients(void) const noexcept;

            PizzaType getType() const noexcept;
            static int getType(std::string const &s);
            std::string getTypeS() const noexcept;
            PizzaSize getSize() const noexcept;
            static int getSize(std::string const &s);
            std::string getSizeS() const noexcept;
        private:
            std::chrono::milliseconds _time;
            PizzaType _type;
            PizzaSize _size;
            std::string _pack;
            std::string _unpack;
            std::vector<Ingredient> _ingredients;
    };
}

#endif /* !PIZZA_HPP_ */

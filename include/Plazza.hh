/*
** Epitech project, tek2.
** Clement-Muth, jonathan-Cohen && Sarah-Keppler
** Plazza
*/

#ifndef PLAZZA_HPP
#define PLAZZA_HPP

#include <vector>

namespace Plazza
{
    enum class PizzaType : std::size_t
    {
        Regina = 1,
        Margarita = 2,
        Americana = 4,
        Fantasia = 8
    };

    enum class PizzaSize : std::size_t
    {
        S = 1,
        M = 2,
        L = 4,
        XL = 8,
        XXL = 16
    };

    enum Ingredient
    {
        DOE,
        TOMATO,
        GRUYERE,
        HAM,
        MUSHROOMS,
        STEAK,
        EGGPLANT,
        GOAT_CHEESE,
        CHIEF_LOVE
    };
    const std::vector<Ingredient> margarita {
        Ingredient::DOE, Ingredient::TOMATO, Ingredient::GRUYERE
    };
    const std::vector<Ingredient> regina {
        Ingredient::DOE, Ingredient::TOMATO, Ingredient::GRUYERE, Ingredient::HAM, Ingredient::MUSHROOMS
    };
    const std::vector<Ingredient> americana {
        Ingredient::DOE, Ingredient::TOMATO, Ingredient::GRUYERE, Ingredient::STEAK
    };
    const std::vector<Ingredient> fantasia {
        Ingredient::DOE, Ingredient::TOMATO, Ingredient::EGGPLANT, Ingredient::GOAT_CHEESE, Ingredient::CHIEF_LOVE
    };

    typedef struct msgbuf {
        long mtype;
        char mtext[100];
    } message_buf;
}

#endif

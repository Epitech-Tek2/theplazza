/*
** Epitech Project, tek2.
** Clement-Muth, jonathan-Cohen && Sarah-Keppler
** Plazza
*/

#include <iostream>
#include <regex>
#include "Exceptions.hpp"
#include "Reception.hpp"

static void usage(char * const binary)
{
    std::cout << "USAGE" << std::endl;
    std::cout << "    " << binary << " f c t" << std::endl << std::endl;
    std::cout << "DESCRIPTION" << std::endl;
    std::cout << "    f      multiplier for the cooking time of the pizzas." << std::endl;
    std::cout << "    c      number of cooks by default in a kitchen." << std::endl;
    std::cout << "    t      time in milliseconds to get each type of ingredients in a kitchen." << std::endl;
}

int main(int const ac, char ** const av)
{
    if (2 == ac && std::regex_match(av[1], std::regex{"(-h)"}))
        usage(av[0]);
    else if (4 == ac) {
        try {
            Plazza::Reception recep{av[1], av[2], av[3]};
            recep.run();
        } catch (Plazza::Exception const &err) {
            std::cerr << err.what() << std::endl;
            return (84);
        }
    } else {
        std::cerr << av[0] << " must have three arguments. -h for more informations." << std::endl;
        return (84);
    }
    return (0);
}

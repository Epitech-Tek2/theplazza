/*
** EPITECH PROJECT, 2021
** B-CCP-400-STG-4-1-theplazza-clement.muth
** File description:
** Cook
*/

#ifndef COOK_HPP_
#define COOK_HPP_

#include "Pizza.hpp"
#include <iomanip>

namespace Plazza {
    class Cook {
        public:
            Cook() noexcept;
            ~Cook() = default;

            void cook(Pizza const pizza) noexcept;
            void endCook(void) noexcept;
            std::string displayStatus(void) noexcept;
        private:
            bool _cook;
            Pizza _pizza;
            std::chrono::high_resolution_clock::time_point _begin;
            std::chrono::high_resolution_clock::time_point _actual;
    };
}

#endif /* !COOK_HPP_ */

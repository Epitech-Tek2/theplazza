/*
** Epitech project, tek2.
** Clement-Muth, jonathan-Cohen && Sarah-Keppler
** Plazza
*/

#ifndef PLAZZA_ORDER_HPP
#define PLAZZA_ORDER_HPP

#include <string>
#include <vector>
#include <fstream>
#include "Pizza.hpp"

namespace Plazza
{
    class Order
    {
    public:
        Order(std::string const &s, double const factor);
        ~Order() = default;

        /**
         * @brief Get the writing format of the order
         */
        std::string log(void) const noexcept;

        /**
         * @brief Upate the order if the order contain the pizza to do
         * 
         * @param pizza to check
         */
        bool update(Pizza const &pizza) noexcept;

        /**
         * @brief Get the vector of pack pizza to send to message queue
         */
        std::vector<std::string> getNoteForKitchens(void) const noexcept;

        /**
         * @brief Get the Nbr Pizza in the order
         */
        int getNbrPizza(void) const noexcept;

        /**
         * @brief Check if an order is complete
         */
        bool iscompleted(void) noexcept;

        /**
         * @brief Display the status of an order
         */
        void displayStatus(void) const noexcept;

    private:
        int _nbrPizzaInOrder;
        std::vector<Pizza> _pizzas;
        std::vector<int> _nbrmax;
        std::vector<int> _nbrdone;
        std::vector<bool> _isBeingBaked;// unused
    };
}

std::ofstream& operator<<(std::ofstream &out, Plazza::Order const &order);

#endif

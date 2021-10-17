/*
** Epitech project, tek2.
** Clement-Muth, jonathan-Cohen && Sarah-Keppler
** Plazza
*/

#ifndef PLAZZA_RECEPTION_HPP
#define PLAZZA_RECEPTION_HPP

#include <string>
#include <vector>
#include <cmath>

#include "Mutex.hpp"
#include "ConditionVariable.hpp"
#include "UniqueLock.hpp"
#include "Thread.hpp"

#include "Pizza.hpp"
#include "Sender.hpp"
#include "Receiver.hpp"
#include "Kitchen.hpp"
#include "Order.hpp"
#include "Process.hpp"

namespace Plazza
{
    #define NBNEWKITCHEN std::ceil(nbcurrentPizza / (_nbrCooks * 2.0) - _nbrKitchens)

    class Reception
    {
    public:
        Reception() = delete;
        Reception(std::string const &factor, std::string const &nbrCooks, std::string const &time);
        ~Reception();

        /**
         * @brief Manage the correct run of the reception
         */
        void run(void);
    private:

        /**
         * @brief 
         * 
         * @param factor 
         * @param nbrCooks 
         * @param time 
         */
        void Parsing(std::string const &factor, std::string const &nbrCooks, std::string const &time);

        /**
         * @brief Create a Kitchen object
         * 
         * @param nbrNewKitchen number of new kitchen to create
         */
        void createKitchen(std::size_t const nbrNewKitchen);

        /**
         * @brief Remove All the kitchen that are still running
         */
        void removeKitchen(void);

        /**
         * @brief Send the order pizza by pizza
         * 
         * @param order to be send
         */
        void handleQueue(Order const &order);

        /**
         * @brief create an order by the string given in input
         * 
         * @param s get by getline
         * @return true: is valid order
         * @return false: invalid order
         */
        bool handleOrder(std::string const &s);

        /**
         * @brief manage the number of kitchen: only add
         */
        void handleKitchen(void);

        /**
         * @brief [Counter] manage ended order
         * 
         * @param pizza 
         */
        void updateOrder(Pizza const &pizza);

        /**
         * @brief manage kitchen: only delete
         */
        void updateKitchen(void);

        /**
         * @brief [Is threaded] manage reception of ended pizza
         */
        void counter(void);

        /**
         * @brief Display the status of all the kitchen and cooks
         */
        void displayStatus(void);

        /**
         * @brief Write in the log file the order given in parameter
         * 
         * @param order to log into file
         */
        void record(Order const &order) const;

        /**
         * @brief get the current number of pizza
         */
        int currentPizza(void) noexcept;

    private:
        std::size_t _nbrCooks;
        std::atomic<int> _nbrKitchens;
        double _factor;
        double _time;
        enc::Mutex _msender;
        Sender _sender;
        Sender _kitchenSender;
        Receiver _receiver;
        enc::Mutex _morders;
        std::vector<Order> _orders;
        enc::Thread _tcounter;
    };
}

#endif

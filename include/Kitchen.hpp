/*
** EPITECH PROJECT, 2021
** threadpool
** File description:
** Kitchen
*/

#ifndef KITCHEN_HPP_
#define KITCHEN_HPP_

#include "ConditionVariable.hpp"
#include "UniqueLock.hpp"
#include "Mutex.hpp"
#include "Thread.hpp"

#include "ThreadPool.hpp"
#include "Receiver.hpp"
#include "Stream.hpp"
#include "Queue.hpp"
#include "Pizza.hpp"
#include "Plazza.hh"
#include "Stock.hpp"
#include "Sender.hpp"

namespace Plazza {
    enum status {
        STOP,
        WAIT,
        RUN
    };

    class Kitchen
    {
        public:
            Kitchen(std::size_t const id, int const cooks, double const multiplier,
            std::size_t const regeneration, std::string const keyfile, Sender const &sender/*, Sender const &senderback*/);
            ~Kitchen();

            void run(void);
        private:
            void commands(void);
            void stock(void);
            void done(void);
            void send(Pizza const pizza);
            void displayStatus(void);
        private:
            std::size_t _id;
            int _e;
            bool _forceClose;
            Receiver _receiver;
            Sender _senderback;
            Sender _sender;
            std::size_t _cooks;
            std::size_t _inprogress;
            status _status;
            double _multiplier;
            enc::Mutex _morders;
            std::vector<Pizza> _orders;
            ThreadPool _pool;
            Stock _stock;
            enc::Mutex _mkitchen;
            enc::ConditionVariable _ckitchen;
            enc::Thread _tstock;
            enc::Thread _tcommand;
            enc::Thread _tdone;
    };
}

#endif /* !KITCHEN_HPP_ */

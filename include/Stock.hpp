/*
** EPITECH PROJECT, 2021
** threadpool
** File description:
** Stock
*/

#ifndef STOCK_HPP_
#define STOCK_HPP_

#include <map>
#include <chrono>
#include <mutex>
#include <thread>
#include <iomanip>
#include <condition_variable>

#include "Mutex.hpp"
#include "ConditionVariable.hpp"

#include "Exceptions.hpp"
#include "Plazza.hh"
#include "Pizza.hpp"
#include "Stream.hpp"

namespace Plazza {
    class Stock {
        public:
            Stock() = delete;
            Stock(std::size_t const regeneration) noexcept;
            ~Stock() = default;

            bool canCook(Pizza const &pizza);
            bool generate(void);
            void stop(void);
            std::string displayStatus(void);
        private:
            bool _stop;
            std::chrono::milliseconds _regeneration;
            enc::ConditionVariable _cvstock;
            enc::Mutex _mstock;
            std::map<Ingredient, std::size_t> _stock;
    };
}

#endif /* !STOCK_HPP_ */

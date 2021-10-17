/*
** EPITECH PROJECT, 2021
** ex5
** File description:
** SafeQueue
*/

#ifndef SAFEQUEUE_HPP_
#define SAFEQUEUE_HPP_

#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>

#include "Mutex.hpp"
#include "ConditionVariable.hpp"
#include "UniqueLock.hpp"

#include "Stream.hpp"
#include "Pizza.hpp"

namespace safe {
    template<typename T>
    class Queue {
        public:
            Queue() noexcept;
            ~Queue() = default;

            void push(T value);
            bool pop(T &value);

            void stop(void);
            std::string dump(void);
        private:
            bool _stop;
            bool _ready;
            enc::Mutex _mutex;
            std::deque<T> _queue;
            enc::ConditionVariable _cv;
    };
}

#endif /* !SAFEQUEUE_HPP_ */

/*
** EPITECH PROJECT, 2021
** threadpool
** File description:
** ThreadPool
*/

#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <vector>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <stdexcept>
#include <sstream>
#include <iostream>
#include <map>

#include "ConditionVariable.hpp"
#include "Mutex.hpp"
#include "Thread.hpp"

#include "Queue.hpp"
#include "Exceptions.hpp"
#include "Stream.hpp"
#include "Cook.hpp"

namespace Plazza {
    class ThreadPool {
    public:
        ThreadPool(std::size_t const threads);
        ~ThreadPool() = default;

        void stop(void);
        void enqueue(Pizza const &pizza);
        bool dequeue(Pizza &pizza);
        std::string displayStatus(void);
    private:
        void worker(std::size_t const i);
        bool cooker(Pizza const &pizza);
    private:
        bool _run;
        std::size_t _nworker;
        std::atomic<std::size_t> _working;
        std::vector<enc::Thread> _workers;
        enc::Mutex _mcooker;
        std::map<std::size_t, Cook> _cookers;
        safe::Queue<Pizza> _wait;
        safe::Queue<Pizza> _done;
        enc::ConditionVariable _cvworker;
    };
}

#endif

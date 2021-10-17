/*
** EPITECH PROJECT, 2021
** ex10
** File description:
** ThreadPool
*/

#include "ThreadPool.hpp"

Plazza::ThreadPool::ThreadPool(std::size_t const threads)
 : _run(true), _nworker(threads), _working(0)
{
    for (std::size_t i = 0; i < threads; ++i) {
        {
            enc::UniqueLock lock(_mcooker);
            _cookers[i] = Cook();
        }
        _workers.emplace_back(enc::Thread(&Plazza::ThreadPool::worker, this, i));
    }
}

bool Plazza::ThreadPool::cooker(Pizza const &pizza)
{
    enc::UniqueLock lock(_mcooker);

    if (_cvworker.wait_for(lock, pizza.getTime()) == std::cv_status::no_timeout) {
        return (false);
    }
    _done.push(pizza);
    return (true);
}

void Plazza::ThreadPool::worker(std::size_t const id)
{
    Pizza pizza;

    while (true) {
        if (!_wait.pop(pizza))
            return;
        ++_working;
        {
            enc::UniqueLock lock(_mcooker);

            _cookers.at(id).cook(pizza);
        }
        if (!cooker(pizza))
            return;
        {
            enc::UniqueLock lock(_mcooker);

            _cookers.at(id).endCook();
        }
        --_working;
    }
}

void Plazza::ThreadPool::enqueue(Pizza const &pizza)
{
    _wait.push(pizza);
}

bool Plazza::ThreadPool::dequeue(Pizza &pizza)
{
    return (_done.pop(pizza));
}

std::string Plazza::ThreadPool::displayStatus(void)
{
    std::stringstream s;

    s << "    " << "Pizza(s) in queue:" << std::endl;
    s << _wait.dump();
    s << "    " << "Cooks: " << _nworker << std::endl;
    {
        enc::UniqueLock lock(_mcooker);

        for (std::map<std::size_t, Cook>::iterator it = _cookers.begin(); it != _cookers.end(); ++it) {
            s << "        Cook n°" << std::distance(_cookers.begin(), it) << ": ";
            s << it->second.displayStatus();
        }
    }
    return (s.str());
}

void Plazza::ThreadPool::stop(void)
{
    _wait.stop();
    _done.stop();
    {
        enc::UniqueLock lock(_mcooker);

        _cvworker.notify_all();
    }
    for (enc::Thread &worker: _workers)
        worker.join();
}

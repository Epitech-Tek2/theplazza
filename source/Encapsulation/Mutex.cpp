/*
** EPITECH PROJECT, 2021
** B-CCP-400-STG-4-1-theplazza-clement.muth
** File description:
** Mutex
*/

#include "Mutex.hpp"

void enc::Mutex::lock(void)
{
    _mutex.lock();
}

void enc::Mutex::unlock(void)
{
    _mutex.unlock();
}

std::mutex &enc::Mutex::variable(void) noexcept
{
    return (_mutex);
}

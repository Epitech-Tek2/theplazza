/*
** EPITECH PROJECT, 2021
** B-CCP-400-STG-4-1-theplazza-clement.muth
** File description:
** UniqueLock
*/

#include "UniqueLock.hpp"

enc::UniqueLock::UniqueLock(Mutex &mutex) : _lock(mutex.variable())
{}

std::unique_lock<std::mutex> &enc::UniqueLock::variable(void) noexcept
{
    return (_lock);
}

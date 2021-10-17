/*
** EPITECH PROJECT, 2021
** B-CCP-400-STG-4-1-theplazza-clement.muth
** File description:
** Thread
*/

#include "Thread.hpp"

enc::Thread::~Thread() {
    if (_thread.joinable())
        _thread.join();
}

enc::Thread::Thread(Thread &&t) noexcept
{
    _thread.swap(t.variable());
}

void enc::Thread::join(void)
{
    if (_thread.joinable())
        _thread.join();
}

std::thread &enc::Thread::variable(void) noexcept
{
    return (_thread);
}

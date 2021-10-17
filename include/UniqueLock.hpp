/*
** EPITECH PROJECT, 2021
** B-CCP-400-STG-4-1-theplazza-clement.muth
** File description:
** UniqueLock
*/

#ifndef UNIQUELOCK_HPP_
#define UNIQUELOCK_HPP_

#include "Mutex.hpp"

#include <mutex>

namespace enc {
    class UniqueLock {
    public:
        UniqueLock() = delete;
        UniqueLock(Mutex &mutex);
        ~UniqueLock() = default;

        std::unique_lock<std::mutex> &variable(void) noexcept;
    private:
        std::unique_lock<std::mutex> _lock;
    };
}

#endif /* !UNIQUELOCK_HPP_ */

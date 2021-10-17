/*
** EPITECH PROJECT, 2021
** B-CCP-400-STG-4-1-theplazza-clement.muth
** File description:
** Mutex
*/

#ifndef MUTEX_HPP_
#define MUTEX_HPP_

#include <mutex>

namespace enc {
    class Mutex {
    public:
        Mutex() = default;
        ~Mutex() = default;

        void lock(void);
        void unlock(void);

        std::mutex &variable(void) noexcept;
    private:
        std::mutex _mutex;
    };
}

#endif /* !MUTEX_HPP_ */

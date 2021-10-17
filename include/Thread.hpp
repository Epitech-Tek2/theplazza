/*
** EPITECH PROJECT, 2021
** B-CCP-400-STG-4-1-theplazza-clement.muth
** File description:
** Thread
*/

#ifndef THREAD_HPP_
#define THREAD_HPP_

#include <thread>
#include <iostream>

#include "Exceptions.hpp"

namespace enc {
    class Thread {
        public:
            Thread() noexcept = default;
            Thread(Thread &) = delete;
            Thread(const Thread &) = delete;
            Thread(const Thread &&) = delete;
            ~Thread();

            Thread(Thread &&t) noexcept;

            template<typename _Callable, typename... _Args>
            Thread(_Callable&& f, _Args&&... args) try : _thread(std::forward<_Callable>(f), std::forward<_Args>(args)...)
            {} catch (std::exception const &err) {
                std::cerr << err.what() << std::endl;
                throw Plazza::MajorException("Thread: error to create thread");
            }

            Thread& operator=(const Thread&) = delete;

            std::thread &variable(void) noexcept;

            void join(void);
        private:
            std::thread _thread;
    };
}

#endif /* !THREAD_HPP_ */

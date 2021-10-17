/*
** EPITECH PROJECT, 2021
** ex10
** File description:
** SafeStream
*/

#ifndef SAFESTREAM_HPP_
#define SAFESTREAM_HPP_

#include <iostream>
#include <sstream>
#include <mutex>
#include <ostream>

#include "Mutex.hpp"
#include "UniqueLock.hpp"

enum Code {
    GREEN      = 41,
    RED        = 160,
    YELLOW     = 220,
    BLUE       = 44,
    WHITE      = 15,
    ORANGE     = 166,
    DEFAULT    = 0
};

class Color {
    public:
        Color(Code code) : _code(code) {}
        ~Color() = default;

        Code getCode(void) const noexcept;
    private:
        Code _code;
};

std::ostream& operator<<(std::ostream& os, const Color& mod);

namespace safe {
    class Stream : public std::ostringstream
    {
    public:
        Stream() = default;
        ~Stream();

    private:
        static enc::Mutex _mutexPrint;
    };
}

#endif /* !SAFESTREAM_HPP_ */

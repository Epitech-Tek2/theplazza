/*
** EPITECH PROJECT, 2021
** B-CCP-400-STG-4-1-theplazza-clement.muth
** File description:
** Process
*/

#ifndef PROCESS_HPP_
#define PROCESS_HPP_

#include "Exceptions.hpp"

#include <sys/types.h>
#include <unistd.h>

enum type {
    CHILD,
    PARENT
};

class Process {
    public:
        Process() = default;
        ~Process() = default;

        type create(void);
        void end(int const code) const;
    private:
        pid_t _pid;
};

#endif /* !PROCESS_HPP_ */

/*
** EPITECH PROJECT, 2021
** B-CCP-400-STG-4-1-theplazza-clement.muth
** File description:
** Process
*/

#include "Process.hpp"

type Process::create(void)
{
    _pid = fork();
    if (_pid == -1) {
        throw Plazza::MajorException("Process: failed to fork");
    } else if (_pid == 0) {
        return (CHILD);
    } else {
        return (PARENT);
    }
}

void Process::end(int const code) const
{
    exit(code);
}

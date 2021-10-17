/*
** Epitech Project, tek2.
** Sarah-Keppler
** Plazza
*/

#ifndef PLAZZA_RECEIVER_HPP
#define PLAZZA_RECEIVER_HPP

#include <string>
#include <sys/types.h>
#include <sys/ipc.h>
#include <iostream>

namespace Plazza
{
    class Receiver
    {
    public:
        Receiver() = default;
        Receiver(std::string const &keyfile);
        Receiver(Receiver const &other) = delete;
        ~Receiver() = default;

        Receiver &operator=(Receiver const &other) = delete;

        void init(std::string const &keyfile);
        std::string receive();
    private:
        std::string _file;
        key_t _key;
        int _id;
    };
}

#endif

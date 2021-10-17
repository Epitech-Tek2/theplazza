/*
** Epitech Project, tek2.
** Sarah-Keppler
** Plazza
*/

#ifndef PLAZZA_SENDER_HPP
#define PLAZZA_SENDER_HPP

#include <string>
#include <sys/types.h>
#include <sys/ipc.h>
#include <cmath>
#include "Pizza.hpp"
#include "Plazza.hh"

namespace Plazza
{
    class Sender
    {
    public:
        Sender() = default;
        Sender(std::string const &keyfile);
        ~Sender() = default;

        Sender &operator=(Sender const &other) = delete;

        void init(std::string const &keyfile);
        void send(std::string const &s) const;
        std::string getFile(void) const noexcept;
        void close();
    private:
        std::string _file;
        key_t _key;
        int _id;
    };
}

#endif

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
#include "Pizza.hpp"
#include "Plazza.hh"

namespace Plazza
{
    typedef struct msgbuf {
	long mtype;
	char mtext[100];
    } message_buf;

    class Sender
    {
    public:
        Sender() = default;
        Sender(std::string const keyfile);
        Sender(Sender const &other) = delete;
        ~Sender() = default;

        Sender &operator=(Sender const &other) = delete;
        Sender &operator<<(std::string const s);
        Sender &operator<<(Pizza const pizza);

        void init(std::string const keyfile);
        void send(std::string const s);
        void send(Pizza const pizza);
        void send(PizzaType const type, PizzaSize const size);
        void close();
    private:
        std::string _file;
        key_t _key;
        int _id;
    };
}

#endif

/*
** Epitech Project, tek2.
** Clement-Muth, jonathan-Cohen && Sarah-Keppler
** Plazza
*/

#include <sys/msg.h>
#include "Receiver.hpp"
#include "Exceptions.hpp"
#include "Plazza.hh"

Plazza::Receiver::Receiver(std::string const &keyfile) : _file{keyfile}
{
    if (-1 == (_key = ftok(keyfile.c_str(), 'B')))
        throw IPCException{"ftok, could not create the key."};
    if (-1 == (_id = msgget(_key, 0644)))
        throw IPCException{"msgget, could not connect to the message queue."};
}

void Plazza::Receiver::init(std::string const &keyfile)
{
    _file = keyfile;
    if (-1 == (_key = ftok(keyfile.c_str(), 'B')))
        throw IPCException{"ftok, could not create the key."};
    if (-1 == (_id = msgget(_key, 0644)))
        throw IPCException{"msgget, could not connect to the message queue."};
}

std::string Plazza::Receiver::receive()
{
    message_buf rbuf;
    if (-1 == msgrcv(_id, &rbuf, 100, 1, 0))
        throw IPCException{"msgrcv, could not receive a message."};
    return std::string{rbuf.mtext};
}

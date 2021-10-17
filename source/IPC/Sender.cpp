/*
** Epitech Project, tek2.
** Clement-Muth, jonathan-Cohen && Sarah-Keppler
** Plazza
*/

#include <stdlib.h>
#include <sys/msg.h>
#include "Sender.hpp"
#include "Exceptions.hpp"

Plazza::Sender::Sender(std::string const &keyfile) : _file{keyfile}
{
    system(std::string{"touch " + _file}.c_str());
    if (-1 == (_key = ftok(_file.c_str(), 'B')))
        throw IPCException{"ftok, could not create the key."};
    if (-1 == (_id = msgget(_key, 0644 | IPC_CREAT)))
        throw IPCException{"msgget: could not create the message queue."};
}

void Plazza::Sender::init(std::string const &keyfile)
{
    _file = keyfile;
    system(std::string{"touch " + _file}.c_str());
    if (-1 == (_key = ftok(_file.c_str(), 'B')))
        throw IPCException{"ftok, could not create the key."};
    if (-1 == (_id = msgget(_key, 0644 | IPC_CREAT)))
        throw IPCException{"msgget: could not create the message queue."};
}

std::string Plazza::Sender::getFile(void) const noexcept
{
    return (_file);
}

void Plazza::Sender::send(std::string const &message) const
{
    message_buf mb;
    mb.mtype = 1;
    strcpy(mb.mtext, message.c_str());
    if (-1 == msgsnd(_id, &mb, message.size() + 1, 0))
        throw IPCException{"msgctl: could not send a message."};
}

void Plazza::Sender::close()
{
    if (-1 == msgctl(_id, IPC_RMID, NULL))
        throw IPCException{"msgctl: could not close the message queue."};    
}

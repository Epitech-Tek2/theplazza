/*
** EPITECH PROJECT, 2021
** threadpool
** File description:
** Kitchen
*/

#include "Kitchen.hpp"

const std::array<std::string, 3> sstatus {
    "Stop",
    "Wait",
    "Run"
};

Plazza::Kitchen::Kitchen(std::size_t const id, int const cooks, double const multiplier,
std::size_t const regeneration, std::string const keyfile, Sender const &sender)
 : _id(id),
 _e(0),
 _forceClose(false),
 _receiver(keyfile),
 _senderback(keyfile),
 _sender(sender),
 _cooks(cooks),
 _inprogress(0),
 _status(RUN),
 _multiplier(multiplier),
 _pool(cooks),
 _stock(regeneration),
 _mkitchen(),
 _ckitchen(),
 _tstock(&Plazza::Kitchen::stock, this),
 _tcommand(&Plazza::Kitchen::commands, this),
 _tdone(&Plazza::Kitchen::done, this)
{}

Plazza::Kitchen::~Kitchen()
{
    _pool.stop();
    _stock.stop();
    _tstock.join();
    _tcommand.join();
    _tdone.join();
}

void Plazza::Kitchen::send(Pizza const pizza)
{
    _pool.enqueue(pizza);
    ++_e;
}

void Plazza::Kitchen::displayStatus(void)
{
    std::stringstream s;

    s << "Kitchen n°" << _id << ": (status: " << sstatus[_status] << ")" << std::endl;
    s << "    " << "Pizza(s) waiting for stock:" << std::endl;
    {
        enc::UniqueLock lock(_morders);
        if (_orders.empty())
            s << "        Empty" << std::endl;
        for (std::vector<Pizza>::const_iterator it = _orders.cbegin(); it != _orders.cend(); ++it)
            s << "        " << it->unpack() << std::endl;
    }
    s << _pool.displayStatus();
    s << _stock.displayStatus();
    std::cout << s.str() << std::endl;
}

void Plazza::Kitchen::commands(void)
{
    std::string line;

    while (true) {
        try {
            line = _receiver.receive();
        } catch (IPCException const &err) {
            return;
        }
        {
            enc::UniqueLock lock(_mkitchen);

            if (_status == STOP) {
                return;
            } else if (!line.compare("force close")) {
                _forceClose = true;
                _status = STOP;
                _ckitchen.notify_all();
                return;
            } else if (!line.compare("close")) {
                continue;
            } else if (!line.compare("status")) {
                displayStatus();
                continue;
            }else if (_inprogress >= _cooks * 2) {
                // Remettre la commande dans la message queue
                try {
                    _senderback.send(line);
                } catch (IPCException const &err) {
                    return;
                }
                continue;
            } else if (!_inprogress) {
                _ckitchen.notify_all();
            }
            ++_inprogress;
        }
        try {
            Pizza pizza(line, _multiplier);
            if (_stock.canCook(pizza)) {
                send(pizza);
            } else {
                {
                    enc::UniqueLock lock(_morders);
                    _orders.push_back(pizza);
                }
            }
        } catch (MinorException const &Exception) {
            std::cerr << Exception.what() << std::endl;
        }
    }
}

void Plazza::Kitchen::stock(void)
{
    while (true) {
        if (!_stock.generate())
            return;
        {
            enc::UniqueLock lock(_morders);

            for (std::vector<Pizza>::iterator i = _orders.begin(); i != _orders.end();) {
                if (_stock.canCook(*i)) {
                    send(*i);
                    i = _orders.erase(i);
                } else {
                    ++i;
                }
            }
        }
    }
}

void Plazza::Kitchen::done(void)
{
    Pizza pizza;

    while (true) {
        if (!_pool.dequeue(pizza))
            return;
        try {
            _sender.send(pizza.pack());
        } catch (IPCException const &err) {
            return;
        }
        {
            enc::UniqueLock lock(_mkitchen);
            --_inprogress;
            if (!_inprogress) {
                _status = WAIT;
                _ckitchen.notify_all();
            }
        }
    }
}

void Plazza::Kitchen::run(void)
{
    while (true) {
        enc::UniqueLock lock(_mkitchen);

        _ckitchen.wait(lock, [this]{ return (_status == WAIT || _status == STOP);});
        if (_forceClose) {
            return;
        } else if (_ckitchen.wait_for(lock, std::chrono::seconds(5)) == std::cv_status::timeout) {
            _sender.send("close");
            _status = STOP;
            return;
        } else {
            _status = RUN;
        }
    }
}

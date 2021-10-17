/*
** Epitech project, tek2.
** Clement-Muth, jonathan-Cohen && Sarah-Keppler $
** Plazza
*/

#include <iostream>
#include <regex>
#include <array>
#include <mutex>
#include <thread>
#include <chrono>
#include <algorithm>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>
#include <fstream>
#include "Reception.hpp"
#include "Exceptions.hpp"
#include "MyLib.hpp"

Plazza::Reception::Reception(std::string const &factor, std::string const &nbrCooks, std::string const &time)
 : _nbrCooks{0},
 _nbrKitchens{0},
 _sender{"order.txt"},
 _kitchenSender{"transfer_back.txt"},
 _receiver{"transfer_back.txt"},
 _tcounter(&Plazza::Reception::counter, this)
{
    try {
        Parsing(factor, nbrCooks, time);
    } catch (MinorException const &err) {
        _kitchenSender.send("force close");
        throw MajorException("Parsing exceptions");
    }
}

Plazza::Reception::~Reception()
{
    _tcounter.join();
    try {
        enc::UniqueLock lock(_msender);

        _sender.close();
        _kitchenSender.close();
    } catch (IPCException const &error) {
        std::cerr << "Reception:" << error.what() << std::endl;
    }
}

void Plazza::Reception::Parsing(std::string const &factor, std::string const &nbrCooks, std::string const &time)
{
    if (std::regex_match(factor, std::regex{R"((?:^|\s)([[:digit:]]+(?:\.[[:digit:]]+)?)(?=$|\s))"})) {
        if (!std::regex_match(factor, std::regex{"[0-9]+"}) && 1.0f <= std::stod(factor))
            throw MinorException{"When the factor is a decimal number, it must be between 0 and 1."};
    } else
        throw MinorException{"The factor must be a positive (decimal) number."};
    _factor = std::stod(factor);
    if (!std::regex_match(nbrCooks, std::regex{"[0-9]+"}))
        throw MinorException{"The number of cooks must be a positive integer."};
    _nbrCooks = std::stoi(nbrCooks);
    if (!_nbrCooks || !_factor)
        throw MinorException{"The time must be a positive (decimal) number."};
    if (!std::regex_match(time, std::regex{R"((?:^|\s)([[:digit:]]+(?:\.[[:digit:]]+)?)(?=$|\s))"}))
        throw MinorException{"The time must be a positive (decimal) number."};
    _time = std::stod(time);
    system("touch served.txt");
}

void Plazza::Reception::createKitchen(std::size_t const nbrNewKitchen)
{
    for (std::size_t e = 0; e < nbrNewKitchen; ++e) {
        Process process;

        if (process.create() == CHILD) {
            try {
                Kitchen kitchen(_nbrKitchens, _nbrCooks, _factor, _time, _sender.getFile(), _kitchenSender/*, _sender*/);

                kitchen.run();
            } catch (Exception const &error) {
                std::cerr << error.what() << std::endl;
                process.end(84);
            }
            process.end(0);
        }
        _nbrKitchens++;
    }
}

void Plazza::Reception::removeKitchen(void)
{
    enc::UniqueLock lock(_msender);

    for (int e = 0; e < _nbrKitchens; ++e) {
        _sender.send("force close");
        _nbrKitchens--;
    }
}

void Plazza::Reception::handleQueue(Order const &order)
{
    std::vector<std::string> notes = order.getNoteForKitchens();
    enc::UniqueLock lock(_msender);

    for (std::vector<std::string>::const_iterator i = notes.cbegin(); i != notes.cend(); ++i) {
        _sender.send(*i);
    }
}

bool Plazza::Reception::handleOrder(std::string const &s)
{
    enc::UniqueLock lock(_morders);
    try {
        Order order(s, _factor);

        _orders.push_back(order);
    } catch (MinorException const &err) {
        std::cerr << "Order: " << err.what() << std::endl;
        return (false);
    }
    return (true);
}

void Plazza::Reception::handleKitchen(void)
{
    int nbcurrentPizza = currentPizza();
    int max = _nbrKitchens * _nbrCooks * 2;

    if (max < 0)
        max = 0;
    if (nbcurrentPizza >= 0  && nbcurrentPizza > max) {
        createKitchen(NBNEWKITCHEN);
    }
}

void Plazza::Reception::updateOrder(Pizza const &pizza)
{
    enc::UniqueLock lock(_morders);

    for (std::vector<Order>::iterator i = _orders.begin(); i != _orders.end(); ++i) {
        if (i->update(pizza)) {
            if (i->iscompleted()) {
                std::cout << "Order complete:" << std::endl;
                i->displayStatus();
                record(*i);
                std::cout << "> ";
                std::cout.flush();
                _orders.erase(i);
            }
            break;
        }
    }
}

void Plazza::Reception::updateKitchen(void)
{
    enc::UniqueLock lock(_msender);

    for (int e = 0; e < _nbrKitchens; ++e) {
        _sender.send("close");
    }
    _nbrKitchens--;
}

void Plazza::Reception::counter(void)
{
    std::string rec;

    while (true) {
        rec = _receiver.receive();
        if (!rec.compare("force close")) {
            removeKitchen();
            return;
        } else if (!rec.find("close")) {
            updateKitchen();
        } else {
            try {
                Pizza pizza(rec, _factor);
                updateOrder(pizza);
            } catch (MinorException const &err) {
                std::cerr << "Counter:" << err.what() << std::endl;
            }
        }
    }
}

void Plazza::Reception::displayStatus(void)
{
    std::cout << "\t\t### PLAZZA STATUS ###" << std::endl;
    std::cout << "\t### ORDERS STATUS ###" << std::endl;
    {
        enc::UniqueLock lock(_morders);

        if (0 == _orders.size())
            std::cout << "No pending orders." << std::endl;
        for (std::vector<Order>::const_iterator it = _orders.cbegin(), et = _orders.cend(); et != it; ++it) {
            std::cout << "Order n°" << std::distance(_orders.cbegin(), it) << ":" << std::endl;
            (*it).displayStatus();
        }
    }
    std::cout << std::endl << "\t### KITCHENS STATUS ###" << std::endl;
    if (0 == _nbrKitchens)
        std::cout << "No kitchens." << std::endl;
    {
        enc::UniqueLock lock(_msender);

        for (int e = 0; e < _nbrKitchens; ++e)
            _sender.send("status");
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    std::cout << std::endl;
}

void Plazza::Reception::record(Order const &order) const
{
    std::ofstream outfile{"log.txt", std::ios::app};

    if (!outfile.is_open())
        throw MinorException{"Could not record."};
    outfile << order;
    outfile.close();
}

int Plazza::Reception::currentPizza(void) noexcept
{
    int nbrCurrentPizzas = 0;
    enc::UniqueLock lock(_morders);

    for (std::vector<Order>::const_iterator i = _orders.cbegin(); i != _orders.cend(); ++i)
        nbrCurrentPizzas += i->getNbrPizza();
    return (nbrCurrentPizzas);
}

void Plazza::Reception::run(void)
{
    std::string line;

    while (1) {
        std::cout << "> ";
        std::cout.flush();
        if (!std::getline(std::cin, line)) {
            _kitchenSender.send("force close");
            return;
        }
        if (!line.compare("")) {
            continue;
        } else if (!line.compare("exit")) {
            _kitchenSender.send("force close");
            return;
        } else if (!line.compare("status")) {
            displayStatus();
        } else {
            if (!handleOrder(line))
                continue;
            handleKitchen();
            handleQueue(_orders.back());
        }
    }
}

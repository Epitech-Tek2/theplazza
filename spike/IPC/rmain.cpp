#include <iostream>
#include <string>
#include "Receiver.hpp"

int main()
{
    Plazza::Receiver receiver{"ex.txt"};
    std::cout << receiver.receive() << std::endl;
    return (0);
}

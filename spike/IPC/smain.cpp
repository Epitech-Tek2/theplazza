#include <iostream>
#include <string>
#include "Sender.hpp"

int main()
{
    try {
	Plazza::Sender sender{"ex.txt"};
	sender.send("Heya");
    } catch (Plazza::Exception const &except) {
	std::cerr << except.what() << std::endl;
    }
    while(1);
    return (0);
}

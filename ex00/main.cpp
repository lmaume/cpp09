#include <iostream>
#include <sstream>
#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
	BitcoinExchange btc;
	if (argc == 2)
		btc.getInput(argv[1]);
	else
		std::cout << "Error: could not open file.\n";
}

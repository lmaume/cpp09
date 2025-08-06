#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <iterator>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <map>

class BitcoinExchange
{
	private:
		std::map<std::string, std::string> _data;
	public:
		void	getInput(char *fileName);
		BitcoinExchange();
		~BitcoinExchange();
};

#endif
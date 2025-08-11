#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <iterator>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <map>

#define ERROR -1

class BitcoinExchange
{
	private:
		std::map<std::string, std::string> _data;
		void	printExchange(std::string value, int i);
	public:
		void	getInput(char *fileName);
		BitcoinExchange();
		~BitcoinExchange();
};

#endif
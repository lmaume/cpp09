#include "BitcoinExchange.hpp"

void print_map(std::map<std::string, std::string>& m)
{
	for (std::map<std::string, std::string>::const_iterator it = m.begin(); it != m.end(); ++it)
		std::cout << it->first << " = " << it->second << "; \n";
}

BitcoinExchange::BitcoinExchange()
{
	std::string	tmp;
	std::ifstream infile("data.csv", std::ifstream::in);
	int			i = 0;
	getline(infile, tmp);
	while (getline(infile, tmp))
	{
		if (tmp.size() > 10)
		{
			i = tmp.find(",");
			_data.insert(std::make_pair(tmp.substr(0, i), tmp.substr(i + 1)));
		}
	}
	infile.close();
	// print_map(_data);
}

BitcoinExchange::~BitcoinExchange()
{

}

bool	isDateValid(std::string date[3], std::string fullDate)
{
	std::stringstream	dateStream(fullDate);
	struct tm			time;
	char				chara;

	int					numericDate[3];
	numericDate[0] = atoi(date[0].c_str());
	numericDate[1] = atoi(date[1].c_str());
	numericDate[2] = atoi(date[2].c_str());

	dateStream >> time.tm_year >> chara >> time.tm_mon >> chara >> time.tm_mday;
	time.tm_hour = 1;
	time.tm_min = 0;
	time.tm_sec = 0;
	mktime(&time);
	if (time.tm_year != numericDate[0] || time.tm_mon != numericDate[1] || time.tm_mday != numericDate[2])
		return false;
	return true;
}

void	BitcoinExchange::getInput(char *fileName)
{
	std::string		tmp;
	std::string		date[3];
	int				i, j = 0;
	double			value = 0;
	std::ifstream	infile(fileName, std::ifstream::in);

	if (infile.is_open() == false)
	{
		std::cout << "Error: could not open file.\n";
		return;
	}
	getline(infile, tmp);
	while (getline(infile, tmp))
	{
		if (tmp.size() >= 10)
		{
			i = tmp.find("-");
			j = tmp.find("-");
			date[0] = tmp.substr(0, i);
			date[1] = tmp.substr(i+1, 2);
			date[2] = tmp.substr(i+j, 2);
			if (isDateValid(date, tmp.substr(0, 10)) == false)
			{
				std::cout << "Error: bad input => " << tmp << "\n";
				tmp = "ERROR";
			}
		}
		if (tmp != "ERROR" && tmp.size() > 10)
		{
			i = tmp.find("|");
			if ((const unsigned long)i == tmp.npos)
			{
				std::cout << "Error: bad input => " << tmp << "\n";
				tmp = "ERROR";
			}
			else if (atof(tmp.substr(i+1).c_str()) > 2147483647)
			{
				std::cout << "Error: too large a number.\n";
				tmp = "ERROR";
			}
			else if (atof(tmp.substr(i+1).c_str()) < 0)
			{
				std::cout << "Error: not a positive number.\n";
				tmp = "ERROR";
			}
			else
			{
				std::map<std::string, std::string>::const_iterator it = _data.lower_bound(tmp.substr(0, i-1));
				std::string tempo = (*it).second;
				value = atof(tmp.substr(i+2).c_str());
				std::cout << tmp.substr(0, i-1) << " => " << tmp.substr(i+1) << " = " << value * atof(tempo.c_str()) << std::endl;
			}
		}
	}

	infile.close();
}

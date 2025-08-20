#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
	std::ifstream	infile("data.csv", std::ifstream::in);
	std::string		tmp;
	int				i = 0;

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
}

BitcoinExchange::~BitcoinExchange()
{

}

void	print_map(std::map<std::string, std::string>& m)
{
	for (std::map<std::string, std::string>::const_iterator it = m.begin(); it != m.end(); ++it)
		std::cout << it->first << " = " << it->second << "; \n";
}

void	BitcoinExchange::printExchange(std::string stringValue, int i)
{
	std::map<std::string, std::string>::const_iterator it = _data.lower_bound(stringValue.substr(0, i-1));
	if (it != _data.begin())
		it--;
	std::string tmp = (*it).second;

	double doubleValue = atof(stringValue.substr(i+2).c_str());
	std::cout << stringValue.substr(0, i-1) << " => " << stringValue.substr(i+2) << " = " << doubleValue * atof(tmp.c_str()) << std::endl;
}

bool	isDateValid(std::string date[3], std::string fullDate)
{
	std::stringstream	dateStream(fullDate);
	struct tm			time;
	char				chara;

	int					numericDate[3];
	numericDate[0] = atoi(date[0].c_str());
	numericDate[1] = atoi(date[1].c_str()) - 1;
	numericDate[2] = atoi(date[2].c_str());

	dateStream >> time.tm_year >> chara >> time.tm_mon >> chara >> time.tm_mday;
	time.tm_mon -= 1;
	time.tm_hour = 1;
	time.tm_min = 0;
	time.tm_sec = 0;
	mktime(&time);

	if (time.tm_year != numericDate[0] || time.tm_mon != numericDate[1] || time.tm_mday != numericDate[2])
		return false;
	return true;
}

int	parseDate(std::string stringValue, int i)
{
	std::string		date[3];

	i = stringValue.find("-");
	int j = stringValue.find("-");
	date[0] = stringValue.substr(0, i);
	date[1] = stringValue.substr(i+1, 2);
	date[2] = stringValue.substr(i+j, 2);
	if (isDateValid(date, stringValue.substr(0, 10)) == false)
	{
		std::cout << "Error: bad input => " << stringValue << "\n";
		return ERROR;
	}
	return i;
}

int	isValueValid(std::string value)
{
	int		i = value.find("|");
	double	doubleValue = atof(value.substr(i+1).c_str());

	if ((const unsigned long)i == value.npos)
	{
		std::cout << "Error: bad input => " << value << "\n";
		return ERROR;
	}
	else if (doubleValue > 1000)
	{
		std::cout << "Error: too large a number.\n";
		return ERROR;
	}
	else if (doubleValue < 0)
	{
		std::cout << "Error: not a positive number.\n";
		return ERROR;
	}
	return i;
}

void	BitcoinExchange::getInput(char *fileName)
{
	std::string		stringValue;
	int				i = 0;
	std::ifstream	infile(fileName, std::ifstream::in);

	if (infile.is_open() == false)
	{
		std::cout << "Error: could not open file.\n";
		return;
	}
	getline(infile, stringValue);
	while (getline(infile, stringValue))
	{
		if (stringValue.size() >= 10)
			i = parseDate(stringValue, i);
		if (i != -1 && stringValue.size() > 10)
		{
			i = isValueValid(stringValue);
			if (i != -1)
				printExchange(stringValue, i);
		}
	}

	infile.close();
}

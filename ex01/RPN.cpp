
#include "RPN.hpp"

RPN::RPN(char** input)
{
	std::string	str;
	size_t		it = 0;
	size_t		length = std::strlen(input[1]);
	
	str = input[1];
	if (str.find_first_not_of("0123456789+-*/ ") != str.npos)
	{
		std::cout << "Error\n";
		return;
	}

	while (it < length)
	{
		this->_operation.push(str[it]);
		it += 2;
	}
	operationMaker();
}

RPN::~RPN()
{

}

int calculator(int a, int b, char sign)
{
	if (sign == '+')
		return a + b;
	else if (sign == '-')
		return a - b;
	else if (sign == '*')
		return a * b;
	else if (sign == '/')
		return a / b;
	return 0;
}

bool isSign(char sign)
{
	if (sign == '+' || sign == '-' || sign == '*' || sign == '/')
		return true;
	return false;
}

void badInput()
{
	std::cerr << "0\n";
	return;
}

void RPN::operationMaker()
{
	int		first;
	int		second;
	char	tmp = _operation.front();

	first = std::atoi(&tmp);
	if (std::isdigit(abs(first) + '0') == false )
		return badInput();
	_operation.pop();

	while (_operation.empty() == false)
	{
		tmp = _operation.front();
		second = std::atoi(&tmp);
		_operation.pop();

		if (std::isdigit(abs(second) + '0') == false || isSign(_operation.front()) == false)
			return badInput();
		else
			first = calculator(first, second, _operation.front());
		_operation.pop();
	}
	std::cout << first << "\n";
	return ;
}


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
		return ;
	}
	while (it < length)
	{
		if (isSign(str[it]) == true)
			this->_operation.push(str[it]);
		else if (isdigit(str[it]) != false)
			this->_digital.push(std::atoi(&str[it]));
		it += 2;
	}
	if (this->_operation.size() != this->_digital.size() - 1)
	{
		std::cout << "0\n";
		return ;
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
	else if (sign == '/' && b != 0)
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
	return ;
}

void RPN::operationMaker()
{
	int		first;
	int		second;

	first = _digital.top();
	_digital.pop();

	while (_operation.empty() == false)
	{
		second = _digital.top();
		_digital.pop();
		first = calculator(first, second, _operation.front());
		_operation.pop();
	}
	std::cout << first << "\n";
	return ;
}

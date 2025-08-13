#ifndef RPN_HPP
# define RPN_HPP

#include <iostream>
#include <queue>
#include <cstdlib>
#include <cstring>

class RPN
{
	private:
		std::queue<char> _operation;
	public:
		void operationMaker();
		RPN(char** input);
		~RPN();
};

#endif
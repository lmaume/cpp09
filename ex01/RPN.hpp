#ifndef RPN_HPP
# define RPN_HPP

#include <iostream>
#include <queue>
#include <stack>
#include <cstdlib>
#include <cstring>

class RPN
{
	private:
		std::queue<char> _operation;
		std::stack<int> _digital;
	public:
		void operationMaker();
		RPN(char** input);
		~RPN();
};

bool	isSign(char sign);

#endif
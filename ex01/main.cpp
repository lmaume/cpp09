#include "RPN.hpp"

int main(int argc, char** argv)
{
	if (argc == 2)
		RPN operation(argv);
	else
		std::cout << "Error\n";
}

#include "PmergeMe.hpp"

int main(int argc, char** argv)
{
	if (argc <= 1)
		return 1;

	PmergeMe<std::vector<int> > merge(argv);
}

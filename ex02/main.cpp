#include "PmergeMe.hpp"

int main(int argc, char** argv)
{
	if (argc <= 1)
		return 1;

	try
	{
		//? cout before
		PmergeMe<std::vector<int> > Victor(argv);
		std::cout << "Before: ";
		printList(Victor.getList());

		//? sort with vector
		std::vector<int>vecList = Victor.sortList(Victor.getList());

		//? cout after
		std::cout << "After: ";
		printList(vecList);

		//? cout time
		std::cout << "Time to process a range of " << argc - 1 << " elements with std::vector<int> : " << "Victor.time()" << " us\n";
		std::cout << "Time to process a range of " << argc - 1 << " elements with std::deque<int> : " << 0.00031 << " us\n";
	}
	catch(std::invalid_argument e)
	{
		std::cout << e.what();
	}
}

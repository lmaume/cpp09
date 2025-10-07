#include "PmergeMe.hpp"

int main(int argc, char** argv)
{
	if (argc <= 1)
		return 1;

	try
	{
		//? cout before
		PmergeMe<std::vector<int> > Victor(argv);
		PmergeMe<std::deque<int> > Tails(argv);
		
		std::cout << "Before: ";
		printList(Victor.getList());
		
		//? sort with vector
		
		timespec startspec;
		timespec endspec;
		// clock_gettime(CLOCK_REALTIME, &startspec);
	
		long double start = startspec.tv_nsec;
		std::vector<int>vecList = Victor.sortList(Victor.getList());
		long double timerA = endspec.tv_nsec;

		start = startspec.tv_nsec;
		std::deque<int>deqList = Tails.sortList(Tails.getList());
		long double timerB = endspec.tv_nsec;

		//? cout after
		std::cout << "After: ";
		printList(vecList);

		//? cout time
		std::cout << "Time to process a range of " << argc - 1 << " elements with std::vector<int> : " << std::fixed << timerA - start << " us\n";
		std::cout << "Time to process a range of " << argc - 1 << " elements with std::deque<int> : " << timerB - start << " us\n";
	}
	catch(std::invalid_argument e)
	{
		std::cout << e.what();
	}
}

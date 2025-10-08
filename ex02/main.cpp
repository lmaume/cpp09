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
		//start vector timer		
		std::clock_t startVector = std::clock();
		//sort vector
		std::vector<int>vecList = Victor.sortList(Victor.getList());
		//end vector timer
		std::clock_t endVector = std::clock();
        double durationVector = 1000000.0 * (endVector - startVector) / CLOCKS_PER_SEC;


		//? sort with deque
		//start deque timer
		std::clock_t startDeque = std::clock();
		//sort deque
		std::deque<int>deqList = Tails.sortList(Tails.getList());
		//end deque timer
		std::clock_t endDeque = std::clock();
        double durationDeque = 1000000.0 * (endDeque - startDeque) / CLOCKS_PER_SEC;


		//? cout after
		std::cout << "After: ";
		printList(vecList);

		//? cout time
		std::cout << "Time to process a range of " << argc - 1 << " elements with std::vector<int> : " << durationVector << " us\n";
		std::cout << "Time to process a range of " << argc - 1 << " elements with std::deque<int> : " << durationDeque << " us\n";
	}
	catch(std::invalid_argument e)
	{
		std::cout << e.what();
	}
}

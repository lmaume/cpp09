#include "PmergeMe.hpp"

bool	isNum(std::string str)
{
	int i = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
	{
		if (std::isdigit(str[i]) == false)
			return false;
		i++;
	}
	return true;
}

template <class T>
void printLists(T first, T second)
{
	if (first.empty() == false)
	{
		std::cout << "\nfirst : ";
		for (size_t i = 0; i < first.size(); i++)
		std::cout << first[i] << " ";
	}
	std::cout << "\n";
	if (second.empty() == false)
	{
		std::cout << "second : ";
		for (size_t i = 0; i < second.size(); i++)
		std::cout << second[i] << " ";
	}
	std::cout << "\n\n" << std::endl;
}

template <class T>
void printList(T List)
{
	if (List.empty() == false)
	{
		std::cout << "\nList : ";
		for (size_t i = 0; i < List.size(); i++)
		std::cout << List[i] << " ";
	}
	std::cout << "\n\n" << std::endl;
}


template <class T>
bool isSorted(T list)
{
	size_t i = 0;

	while (i < list.size())
	{
		if (list[i+1] && list[i] > list[i+1])
			return false;
		i++;
	}
	return true;
}

template <class T>
T PmergeMe<T>::jacobsthalSequence(size_t size)
{
	T sequence;
	size_t a = 0;
	size_t b = 1;
	
	if (size <= 0)
		return sequence;

	// Ajoute les deux premiers termes de la sequence
	sequence.push_back(0);
	if (size >= 1)
		sequence.push_back(1);

	size_t current = 1;
	while (current < size)
	{
		current = b + 2 * a;
		if (current > size)
			break ;
		sequence.push_back(current);
		a = b;
		b = current;
	}

	return sequence;
}

// #################################################################
// #################################################################

template <class T>
PmergeMe<T>::PmergeMe(char** argv)
{
	std::string tmp;
	T list;
	for (int i = 1; argv[i]; i++)
	{
		tmp = argv[i];
		if (isNum(tmp) == false)
		{
			std::cout << "Invalid entry\n";			
			return ;
		}
		list.push_back(std::atoi(argv[i]));
	}
	_jacobsthal = jacobsthalSequence(list.size());
	sortList(list);
}

template <class T>
PmergeMe<T>::~PmergeMe()
{

}



// #################################################################

template <class T>
void makePairs(T *losers, T *winners, int a, int b)
{
	// std::cout << "a is " << a << " and b is " << b << ".";

	if (a > b)
	{
		winners->push_back(a);
		losers->push_back(b);
	}
	else
	{
		winners->push_back(b);
		losers->push_back(a);
	}
}



//?###########################################################################################

template <typename T>
void binaryInsert(T& sorted, int value) 
{
    typename T::iterator low = sorted.begin();
    typename T::iterator high = sorted.end();

    while (low != high) 
    {
        typename T::iterator mid = low + (high - low) / 2;
        if (value < *mid)
            high = mid;
        else
            low = mid + 1;
    }
    sorted.insert(low, value);
}

template <class T>
size_t indexForJacobsthal(T &jacobsthal, size_t size)
{
	size_t i = 0;
	while (jacobsthal[i] < static_cast<int>(size))
		i++;
	return i;
}

template <typename T>
void insertByJacobsthal(T &jacobsthal, T &cont, T &loser)
{
    std::vector<bool> inserted(loser.size(), false);
    size_t i = 0;
    size_t j = indexForJacobsthal(jacobsthal, loser.size());
    size_t tmp = 0;


    while (i < j && i < loser.size())
    {
        size_t index = jacobsthal[i];
        if (tmp == i && inserted[index] == false)
        {
			std::cout << "inserting " << loser[index] << ".\n";
            binaryInsert(cont, loser[index]);
            inserted[index] = true;
        }
        index--;
        while (tmp != i && inserted[index] == false)
        {
			std::cout << "inserting " << loser[index] << ".\n";
            binaryInsert(cont, loser[index]);
            inserted[index] = true;
            index--;
        }
        tmp = i;
        i++;
    }
}


//?###########################################################################################


// template <class T>
// void	PmergeMe<T>::sortList(T list)
// {
// 	T winners;
// 	T losers;

// 	if (list.size() <= 1)
// 		return ;

// 	std::cout << "_jacobsthal\n";
// 	printLists(_jacobsthal, _jacobsthal);
// 	while(list.empty() == false)
// 	{

// 		if (list.size() > 1)
// 		{
// 			makePairs(&losers, &winners, list[0], list[1]);
// 			list.erase(list.begin(), list.begin()+2);
// 		}
// 		else if (list.size() == 1)
// 		{
// 			std::cout << list[0] << "\n";
// 			losers.push_back(list[0]);
// 			list.erase(list.begin(), list.begin()+1);
// 		}
// 		std::cout << "list\n";
// 		printLists(losers, list);
// 	}
// 	sortList(winners);
// 	list = winners;
// 	insertByJacobsthal(_jacobsthal, list, losers);

// 	printLists(losers, list);
// }

template <class T>
void	PmergeMe<T>::sortList(T list)
{
	T winners;
	T losers;
	
	if (list.size() <= 1)
		return ;
		
	printList(_jacobsthal);
	size_t i = 0;
	while(i < list.size() - 1)
	{
		std::cout << "even : " << list[i] << " and " << list[i + 1] << "\n\n";
		
		makePairs(&losers, &winners, list[i], list[i+1]);
		i += 2;
		printLists(losers, winners);
	}
	if (list.size() % 2 != 0)
	{
		std::cout << "odd : " << list[i] << "\n";
		losers.push_back(list[i]);
	}
	std::cout << "before sort, after loop\n";
	printList(winners);

	sortList(winners);
	
	printList(winners);
	list = winners;

	std::cout << "after sort,\n";
	printList(list);

	insertByJacobsthal(_jacobsthal, list, losers);
	
	std::cout << "after insert,\n";
	printList(list);
}
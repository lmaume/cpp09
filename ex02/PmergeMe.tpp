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
		std::cout << "\nfirst list : ";
		for (size_t i = 0; i < first.size(); i++)
		std::cout << first[i] << " ";
	}
	std::cout << "\n";
	if (second.empty() == false)
	{
		std::cout << "second list : ";
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
// #################################################################

template <class T>
void makePairs(T *losers, T *winners, int a, int b)
{
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

template <typename T>
void binaryInsert(T& sorted, const int value) 
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
void insertByJacobsthal(T &jacobsthal, T &list, T &loser)
{
	std::vector<bool> inserted(loser.size(), false);
	size_t size = loser.size();

	if (!loser.empty())
	{
		binaryInsert(list, loser[0]);
		inserted[0] = true;
	}
	size_t prev = 1;
	for (size_t i = 1; i < size; i++)
	{
		size_t index = jacobsthal[i];
		if (index >= size)
			index = size - 1;
		if (!inserted[index])
		{
			binaryInsert(list, loser[index]);
			inserted[index] = true;
		}
		for (size_t j = index - 1; j > prev && j < size; j--)
		{
			if (!inserted[j])
			{
				binaryInsert(list, loser[j]);
				inserted[j] = true;
			}
		}
		prev = index;
	}
	for (size_t i = 0; i < size; i++)
	{
		if (!inserted[i])
		{
			binaryInsert(list, loser[i]);
			inserted[i] = true;
		}
	}
}

//?###########################################################################################


template <class T>
void	PmergeMe<T>::sortList(T &list)
{
	T winners;
	T losers;
	
	if (list.size() <= 1)
		return ;
	size_t i = 0;
	while(i < list.size() - 1)
	{
		makePairs(&losers, &winners, list[i], list[i+1]);
		i += 2;
	}
	if (list.size() % 2 != 0)
		losers.push_back(list[i]);
	
	sortList(winners);
	list = winners;
	insertByJacobsthal(_jacobsthal, list, losers);

	printList(list);
}

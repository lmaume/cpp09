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
void printList(T List)
{
	if (List.empty() == false)
	{
		if (List.size() <= 5)
		{
			for (size_t i = 0; i < List.size(); i++)
			std::cout << List[i] << " ";
		}
		else
		{
			for (size_t i = 0; i < 4; i++)
			std::cout << List[i] << " ";
			std::cout << "[...]";
		}
	}
	std::cout << std::endl;
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

size_t    jacobsthalSequence(size_t n)
{
	return ((pow(2, n) - pow(-1, n)) / 3);
}

// #################################################################
// #################################################################

template <class T>
PmergeMe<T>::PmergeMe(char** argv)
{
	std::string tmp;
	for (int i = 1; argv[i]; i++)
	{
		tmp = argv[i];
		if (isNum(tmp) == false)
			throw(std::invalid_argument("Error\n"));	
		_list.push_back(std::atoi(argv[i]));
	}
	// _jacobsthal = jacobsthalSequence(_list.size());
}

template <class T>
PmergeMe<T>::~PmergeMe()
{
}

template <class T>
T&	PmergeMe<T>::getList()
{
	return this->_list;
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
size_t indexForJacobsthal(size_t size)
{
	size_t i = 0;
	while (jacobsthalSequence(i) < size)
		i++;
	return i;
}

template <typename T>
void insertByJacobsthal(T &list, T &loser)
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
		size_t index = jacobsthalSequence(i);
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
T&	PmergeMe<T>::sortList(T &list)
{
	T winners;
	T losers;
	
	if (list.size() <= 1)
		return list;
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
	insertByJacobsthal(list, losers);
	return list;
}

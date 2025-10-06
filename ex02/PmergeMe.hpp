#ifndef PMERGEME_H
# define PMERGEME_H

# include <iostream>
# include <cstdlib>
# include <vector>
# include <deque>
# include <list>
# include <math.h>


template <class T>
class PmergeMe
{
	private:
		T		_jacobsthal;
		T		_list;
		T		jacobsthalSequence(size_t size);
	public:
		T&	sortList(T &list);
		T&	getList();

		PmergeMe(char** argv);
		~PmergeMe();
};

template <class T>
void	printList(T List);

# include "PmergeMe.tpp"

#endif
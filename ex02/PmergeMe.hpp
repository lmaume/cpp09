#ifndef PMERGEME_H
# define PMERGEME_H

# include <iostream>
# include <cstdlib>
# include <vector>
# include <deque>
# include <list>


template <class T>
class PmergeMe
{
	private:
		T		_jacobsthal;
		T		jacobsthalSequence(size_t size);
		void	sortList(T list);
	public:
		PmergeMe(char** argv);
		~PmergeMe();
};


# include "PmergeMe.tpp"

#endif
#include "PmergeMe.hpp"
#include <algorithm>
#include <ctime>     // 用於 clock() 計時
#include <iomanip>
#include <iostream>
#include <vector>
#include <deque>

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/
PmergeMe::PmergeMe(): timeVector(0), timeDeque(0)
{
}

PmergeMe::PmergeMe(const PmergeMe & src): vec(src.vec), deq(src.deq), timeVector(src.timeVector), timeDeque(src.timeDeque)
{
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/
PmergeMe::~PmergeMe()
{
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/
PmergeMe & PmergeMe::operator=(PmergeMe const & src)
{
	if (this != &src)
	{
		vec = src.vec;
		deq = src.deq;
		timeVector = src.timeVector;
		timeDeque = src.timeDeque;
	}
	return *this;
}

/*
** --------------------------------- METHODS ----------------------------------
*/
PmergeMe::PmergeMe(char *av[]): timeVector(0), timeDeque(0)
{
	parseInput(av);
}

void PmergeMe::parseInput(char* av[])
{
	for (int i = 1; av[i]; i++)
	{
		int num = std::atoi(av[i]);
		if (num <= 0)
		{
			std::cerr << "Error: Only positive integer allowed." << std::endl;
			exit(1);
		}
		vec.push_back(num);
		deq.push_back(num);
	}
}

void PmergeMe::sortVector()
{
	clock_t start = clock();
	mergeInsertSort(vec);
	clock_t end = clock();
	timeVector = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1e6; // 微秒
}

void PmergeMe::sortDeque()
{
	clock_t start = clock();
	mergeInsertSort(deq);
	clock_t end = clock();
	timeDeque = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1e6; // 微秒
}

void PmergeMe::printUnsorted() const
{
	std::cout << "Before: ";
	for (std::vector<int>::const_iterator it = vec.begin(); it != vec.end(); ++it) 
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

void PmergeMe::printSorted() const
{
	std::cout << "After: ";
	for (std::vector<int>::const_iterator it = vec.begin(); it != vec.end(); ++it)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

void PmergeMe::printTimeVector() const
{
	std::cout << "Time to process a range of " << vec.size()
		<< " elements with std::vector: " 
		<< std::fixed << std::setprecision(5) << timeVector << " us" << std::endl;
}

void PmergeMe::printTimeDeque() const
{
	std::cout << "Time to process a range of " << deq.size()
		<< " elements with std::deque: " 
		<< std::fixed << std::setprecision(5) << timeDeque << " us" << std::endl;
}

std::vector<int> PmergeMe::getJacobsthal(int n)
{
	std::vector<int> sequence;
	int j0 = 0;
	int j1 = 1;

	if (n >= j0) sequence.push_back(j0);
	if (n >= j1) sequence.push_back(j1);

	int j_next;
	for (int i = 2; ; i++) {
		j_next = j1 + 2 * j0;
		if (j_next > n) break;
		sequence.push_back(j_next);
		j0 = j1;
		j1 = j_next;
	}
	return sequence;
}

template <typename T>
void PmergeMe::execInsert(T& sorted, const T& tmp) 
{
	std::vector<int> jacobSeq = getJacobsthal(tmp.size());
	typename T::const_iterator it = tmp.begin();
	for (; it != tmp.end(); ++it)
	{
		int value = *it;

		// 使用 lower_bound 尋找插入位置，避免重複調用 binary_search
		typename T::iterator pos = std::lower_bound(sorted.begin(), sorted.end(), value);
		if (pos == sorted.end() || *pos != value)
		{
			sorted.insert(pos, value);
		}
	}
}

template <typename T>
void PmergeMe::mergeInsertSort(T& container)
{
	if (container.size() <= 1)
		return;

	T sorted;
	T tmp;
	typename T::iterator it = container.begin();
	for (; it != container.end(); it += 2)
	{
		typename T::iterator next = it;
		if (++next != container.end())
		{
			if (*it < *next)
			{
				sorted.push_back(*it);
				tmp.push_back(*next);
			}
			else
			{
				sorted.push_back(*next);
				tmp.push_back(*it);
			}
		}
		else
		{
			sorted.push_back(*it);
		}
	}
	std::sort(sorted.begin(), sorted.end());
	execInsert(sorted, tmp);
	container = sorted;
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

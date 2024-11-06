#include "PmergeMe.hpp"
#include <algorithm>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <vector>
#include <deque>

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/
PmergeMe::PmergeMe()
{
}

PmergeMe::PmergeMe(const PmergeMe & src)
{
}

PmergeMe::FJvector()
{
}

PmergeMe::FJvector(const FJvector & src)
{
}

PmergeMe::FJdeque()
{
}

PmergeMe::FJdeque(const FJdeque & src)
{
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/
PmergeMe::~PmergeMe()
{
}

PmergeMe::~FJvector()
{
}

PmergeMe::~FJdeque()
{
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/
PmergeMe & PmergeMe::operator=(PmergeMe const & src)
{
	if (this != &src)
		return *this;
	return *this;
}

PmergeMe & FJvector::operator=(FJvector const & src)
{
	if (this != &src)
		return *this;
	return *this;
}

PmergeMe & FJdeque::operator=(FJdeque const & src)
{
	if (this != &src)
		return *this;
	return *this;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

void PmergeMe::parseInput(char **av)
{
	for (unsigned int i = 1; av[i]; i++)
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

void	PmergeMe::FJvector::execFJ(char **av)
{
	parseInput(av);
	if (this->inpit.size() == 1)
		this->sorted.push_back(this->input.front());
	else
	{
		this->makePairs();
		this->sortPairs();
		this->SortMergeParis();
		this->splitSortedPending();
		this->doInsertOrder();
		this->insertPend();
	}
}

void PmergeMe::FJvector::parseInput(char **av)
{
	for (unsigned int i=1; av[i] != NULL; i++)
		this->input.push_back(atoi(av[i]));
}

void PmergeMe::FJvector::makePairs();
{
	for (unsigned int i=0; i + 1 < this->input.size(); i += 2)
		this->pairs.push_back(std::make_pair(this->input.at(i), this->input.at(i + 1)));
}

void PmergeMe::FJvector::sortPairs()
{
	for (unsigned int i=0; i + 1 < this->pairs.size(); i++)
	{
		if (this->pairs.at(i).first > this->pairs.at(i).second) //see which way is better, ascendant, descendant?
			std::swap(this->pairs.at(i).first, this->pairs.at(i).second);
	}
}

void PmergeMe::FJvector::mergeSortedParis(std::vector<std::pair<int, int> > &tab, int start, int mid, int end)
{
	std::vector<std::pair<int, int>> leftArr(tab.begin() + start, tab.begin() + mid + 1);
	std::vector<std::pair<int, int>> rightArr(tab.begin() + mid + 1, tab.begin() + end + 1);
	unsgined int wholeI = static_cast<unsigned int>(start);
	unsigned int leftI = 0; rightI = 0;

	while (leftI < leftArr.size() && rightI < rightArr.size()) //!
	{
		if (leftArr[leftI].first <= rightArr[rightI].first)
			tab[wholeI++] = leftArr[leftI++];
		else
			tab[wholeI++] = rightArr[rightI++];
	}
	while (leftI < leftArr.size()) //!
		tab[wholeI++] = leftArr[leftI++];
	while (rightI < rightArr.size())
		tab[wholeI++] = rightArr[rightI++];
}

void PmergeMe::FJvector::SortMergeParis(std::vector<std::pair<int, int> > &tab, int start, int end)
{
	int mid = start + (end - start / 2);
	if (start >= end)
		return ;
	this->SortMergeParis(tab, start, mid);
	this->SortMergeParis(tab, start + 1, end);
	this->mergeSortedParis(tab, start, mid, end);
}

void PmergeMe::FJvector::splitSortedPending()
{
	this->sorted.push_back(this->pairs[0].first); //smaller one
	for (unsigned int i=1; i < this->pairs.size(); i++)
		this->pend.push_back(this->pairs[i].second); //bigger to pending
}

std::vector<int> generateJacobsthal(int n) //extra
{
    std::vector<int> jacobsthal;
    jacobsthal.push_back(0);
    jacobsthal.push_back(1);
    

    if(n == 1)
    {
        jacobsthal.pop_back();
        return jacobsthal;
    }
    while (jacobsthal.back() < n) {
        int next = jacobsthal[jacobsthal.size() - 1] + 2 * jacobsthal[jacobsthal.size() - 2];
        if (next >= n) break;
        jacobsthal.push_back(next);
    }
    return jacobsthal;
}

void PmergeMe::FJvector::doInsertOrder()
{
	int lastInsertedNbr = 1;
	std::vector<int> = jacobsthal = generateJacobsthal(this->pending.size());
	for (unsigned int i=0; i < jacobsthal.size(); i++)
	{
		int jacob = jacobsthal[i];
		this->insertOrder.push_back(jacob);
		//
		int pos = jacob - 1;
		while 
	}
}

int PmergeMe::FJvector::binarySearchPos(int pendNum, int start, int end);
void PmergeMe::FJvector::insertPend();



void	PmergeMe::FJdeque::execFJ(char **av);
void PmergeMe::FJdeque::parseInput(char **av);
void PmergeMe::FJdeque::makePairs();
void PmergeMe::FJdeque::sortPairs();
void PmergeMe::FJdeque::SortMergeParis(std::deque<std::pair<int, int> > &tab, int start, int end);
void PmergeMe::FJdeque::mergeSortedParis(std::deque<std::pair<int, int> > &tab, int start, int mid, int end);
void PmergeMe::FJdeque::splitSortedPending();
void PmergeMe::FJdeque::doInsertOrder();
int PmergeMe::FJdeque::binarySearchPos(int pendNum, int start, int end);
void PmergeMe::FJdeque::insertPend();
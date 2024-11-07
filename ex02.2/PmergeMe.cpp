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
	*this = src;
	return ;
}

PmergeMe::FJvector::FJvector()
{
	return ;
}

PmergeMe::FJvector::FJvector(const FJvector & src)
{
	*this = src;
	return ;
}

PmergeMe::FJdeque::FJdeque()
{
	return ;
}

PmergeMe::FJdeque::FJdeque(const FJdeque & src)
{
	*this = src;
	return ;
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/
PmergeMe::~PmergeMe()
{
}

PmergeMe::FJvector::~FJvector()
{
}

PmergeMe::FJdeque::~FJdeque()
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

PmergeMe::FJvector &PmergeMe::FJvector::operator=(FJvector const & src)
{
	if (this != &src)
		return *this;
	return *this;
}

PmergeMe::FJdeque &PmergeMe::FJdeque::operator=(FJdeque const & src)
{
	if (this != &src)
		return *this;
	return *this;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

void PmergeMe::FJvector::parseInput(char **av)
{
	for (unsigned int i = 1; av[i]; i++)
	{
		int num = std::atoi(av[i]);
		if (num <= 0)
		{
			std::cerr << "Error: Only positive integer allowed." << std::endl;
			exit(1);
		}
		this->input.push_back(num);
	}
}

void PmergeMe::printUnsorted() const //!to fix
{
	std::cout << "Before: ";
	for (std::vector<int>::const_iterator it = input.begin(); it != input.end(); ++it) 
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

void PmergeMe::printSorted() const //!to fix
{
	std::cout << "After: ";
	for (std::vector<int>::const_iterator it = sorted.begin(); it != sorted.end(); ++it)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

void	PmergeMe::FJvector::execFJ(char **av)
{
	parseInput(av);
	if (this->input.size() == 1)
		this->sorted.push_back(this->input.front());
	else
	{
		this->makePairs();
		this->sortPairs();
		this->SortMergePairs(this->pairs, 0, this->pairs.size() - 1);
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

void PmergeMe::FJvector::makePairs()
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

void PmergeMe::FJvector::mergeSortedPairs(std::vector<std::pair<int, int> > &tab, int start, int mid, int end)
{
	std::vector<std::pair<int, int>> leftArr(tab.begin() + start, tab.begin() + mid + 1);
	std::vector<std::pair<int, int>> rightArr(tab.begin() + mid + 1, tab.begin() + end + 1);
	unsigned int wholeI = static_cast<unsigned int>(start);
	unsigned int leftI = 0, rightI = 0;

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

void PmergeMe::FJvector::SortMergePairs(std::vector<std::pair<int, int> > &tab, int start, int end)
{
	int mid = start + (end - start / 2);
	if (start >= end)
		return ;
	this->SortMergePairs(tab, start, mid);
	this->SortMergePairs(tab, start + 1, end);
	this->mergeSortedPairs(tab, start, mid, end);
}

void PmergeMe::FJvector::splitSortedPending()
{
	this->sorted.push_back(this->pairs[0].first); //smaller one
	for (unsigned int i=1; i < this->pairs.size(); i++)
		this->pending.push_back(this->pairs[i].second); //bigger to pending
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
	std::vector<int> jacobsthal = generateJacobsthal(this->pending.size());
	for (unsigned int i=0; i < jacobsthal.size(); i++)
	{
		int jacob = jacobsthal[i];
		this->insertOrder.push_back(jacob);
		//
		int pos = jacob - 1;
		while (pos > lastInsertedNbr)
			this->insertOrder.push_back(pos--);
		lastInsertedNbr = jacob;
	}
}

int PmergeMe::FJvector::binarySearchPos(int pendNum, int start, int end)
{
	int mid = (start + end) / 2;

	if (end <= start)
		return (pendNum > this->sorted.at(start) ? (start + 1) : start);
	if (pendNum == this->sorted.at(mid))
		return (mid + 1);
	if (pendNum > this->sorted.at(mid))
		return (this->binarySearchPos(pendNum, mid + 1, end));
	return (this->binarySearchPos(pendNum, start, mid - 1));
}

void PmergeMe::FJvector::insertPend()
{
	for (unsigned int i=0; i < this->insertOrder.size(); i++)
	{
		int pendVal = this->pending[this->insertOrder[i]];
		int pos = binarySearchPos(pendVal, 0, this->sorted.size() - 1);
		this->sorted.insert(this->sorted.begin() + pos, pendVal);
	}
}



void PmergeMe::FJdeque::execFJ(char **av)
{

}

void PmergeMe::FJdeque::parseInput(char **av)
{

}

void PmergeMe::FJdeque::makePairs()
{

}

void PmergeMe::FJdeque::sortPairs()
{

}

void PmergeMe::FJdeque::SortMergePairs(std::deque<std::pair<int, int> > &tab, int start, int end)
{

}

void PmergeMe::FJdeque::mergeSortedPairs(std::deque<std::pair<int, int> > &tab, int start, int mid, int end)
{

}

void PmergeMe::FJdeque::splitSortedPending()
{

}

void PmergeMe::FJdeque::doInsertOrder()
{

}

int PmergeMe::FJdeque::binarySearchPos(int pendNum, int start, int end)
{

}

void PmergeMe::FJdeque::insertPend()
{

}

void PmergeMe::runAndTimeVector(char **av) {
    clock_t start = clock();
    fjv.execFJ(av);  // 假設這個函數執行排序並將結果存儲於 fjv.sorted
    clock_t end = clock();
    timeVector = static_cast<double>(end - start) / CLOCKS_PER_SEC;
}

void PmergeMe::runAndTimeDeque(char **av) {
    clock_t start = clock();
    fjd.execFJ(av);  // 假設這個函數執行排序並將結果存儲於 fjd.sorted
    clock_t end = clock();
    timeDeque = static_cast<double>(end - start) / CLOCKS_PER_SEC;
}

void PmergeMe::runAndTimeVector(char **av) {
    clock_t start = clock();
    fjv.execFJ(av);  // 假設這個函數執行排序並將結果存儲於 fjv.sorted
    clock_t end = clock();
    timeVector = static_cast<double>(end - start) / CLOCKS_PER_SEC;
}

void PmergeMe::runAndTimeDeque(char **av) {
    clock_t start = clock();
    fjd.execFJ(av);  // 假設這個函數執行排序並將結果存儲於 fjd.sorted
    clock_t end = clock();
    timeDeque = static_cast<double>(end - start) / CLOCKS_PER_SEC;
}
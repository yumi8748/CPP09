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
            std::cerr << "Error: " << std::endl;
            throw std::invalid_argument("Invalid input!");
        }
        this->input.push_back(num);
    }
}

void PmergeMe::printUnsorted() const
{
    std::cout << "Before: ";
    for (std::vector<int>::const_iterator it = this->input.begin(); it != this->input.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

void PmergeMe::printSorted() const
{
    std::cout << "After: ";
    for (std::vector<int>::const_iterator it = this->sorted.begin(); it != this->sorted.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

void PmergeMe::FJvector::execFJ(char **av)
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

void PmergeMe::FJvector::makePairs()
{
    for (unsigned int i = 0; i + 1 < this->input.size(); i += 2)
        this->pairs.push_back(std::make_pair(this->input.at(i), this->input.at(i + 1)));
}

void PmergeMe::FJvector::sortPairs()
{
    for (unsigned int i = 0; i + 1 < this->pairs.size(); i++)
    {
        if (this->pairs.at(i).first > this->pairs.at(i).second)
            std::swap(this->pairs.at(i).first, this->pairs.at(i).second);
    }
}

void PmergeMe::FJvector::mergeSortedPairs(std::vector<std::pair<int, int>>& tab, int start, int mid, int end)
{
    std::vector<std::pair<int, int>> leftArr(tab.begin() + start, tab.begin() + mid + 1);
    std::vector<std::pair<int, int>> rightArr(tab.begin() + mid + 1, tab.begin() + end + 1);
    unsigned int wholeI = static_cast<unsigned int>(start);
    unsigned int leftI = 0, rightI = 0;

    while (leftI < leftArr.size() && rightI < rightArr.size())
    {
        if (leftArr[leftI].first <= rightArr[rightI].first)
            tab[wholeI++] = leftArr[leftI++];
        else
            tab[wholeI++] = rightArr[rightI++];
    }
    while (leftI < leftArr.size())
        tab[wholeI++] = leftArr[leftI++];
    while (rightI < rightArr.size())
        tab[wholeI++] = rightArr[rightI++];
}

void PmergeMe::FJvector::SortMergePairs(std::vector<std::pair<int, int>>& tab, int start, int end)
{
    int mid = start + (end - start) / 2;
    if (start >= end)
        return;
    this->SortMergePairs(tab, start, mid);
    this->SortMergePairs(tab, mid + 1, end);
    this->mergeSortedPairs(tab, start, mid, end);
}

void PmergeMe::FJvector::splitSortedPending()
{
    this->sorted.push_back(this->pairs[0].first); // smaller one
    for (unsigned int i = 1; i < this->pairs.size(); i++)
        this->pending.push_back(this->pairs[i].second); // bigger to pending
}

std::vector<int> PmergeMe::FJvector::generateJacobsthal(int n)
{
    std::vector<int> jacobsthal;
    jacobsthal.push_back(0);
    jacobsthal.push_back(1);

    if (n == 1)
    {
        jacobsthal.pop_back();
        return jacobsthal;
    }
    while (jacobsthal.back() < n)
    {
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
    for (unsigned int i = 0; i < jacobsthal.size(); i++)
    {
        int jacob = jacobsthal[i];
        this->insertOrder.push_back(jacob);
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
    if (this->pending.empty() || this->insertOrder.empty())
        return;
    for (int pos : this->insertOrder)
    {
        int val = this->pending[pos - 1];
        int insertPos = this->binarySearchPos(val, 0, this->sorted.size() - 1);
        this->sorted.insert(this->sorted.begin() + insertPos, val);
    }
    if (this->input.size() % 2 == 1)
    {
        int val = this->input.back();
        int insertPos = this->binarySearchPos(val, 0, this->sorted.size() - 1);
        this->sorted.insert(this->sorted.begin() + insertPos, val);
    }
}

void PmergeMe::runAndTimeVector(char **av)
{
    clock_t start = clock();
    this->fjv.execFJ(av);
    clock_t end = clock();
    this->timeVector = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000.0; // microseconds
}

void PmergeMe::runAndTimeDeque(char **av)
{
    clock_t start = clock();
    this->fjd.execFJ(av);
    clock_t end = clock();
    this->timeDeque = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000.0; // microseconds
}

void PmergeMe::printTimeVector() const
{
    std::cout << "Time to process a range of " << this->fjv.getSorted().size()
              << " elements with std::vector: "
              << std::fixed << std::setprecision(5) << this->timeVector << " us" << std::endl;
}

void PmergeMe::printTimeDeque() const
{
    std::cout << "Time to process a range of " << this->fjd.getSorted().size()
              << " elements with std::deque: "
              << std::fixed << std::setprecision(5) << this->timeDeque << " us" << std::endl;
}

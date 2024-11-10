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
	{
        fjv = src.fjv;
        fjd = src.fjd;
        timeVector = src.timeVector;
        timeDeque = src.timeDeque;
    }
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

void PmergeMe::printUnsorted() const
{
    std::cout << "Before: ";
    for (std::vector<int>::const_iterator it = fjv.getInput().begin(); it != fjv.getInput().end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

void PmergeMe::printSorted() const
{
    std::cout << "After: ";
    for (std::vector<int>::const_iterator it = fjv.getSorted().begin(); it != fjv.getSorted().end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

void PmergeMe::FJvector::parseInput(char **av)
{
    for (unsigned int i = 0; av[i]; i++)
    {
        int num = std::atoi(av[i]);
        if (num <= 0)
        {
            std::cerr << "Error: " << std::endl;
            throw std::invalid_argument("Invalid input!");
        }
        input.push_back(num);
    }
}

void PmergeMe::FJvector::execFJ(char **av)
{
    // parseInput(av);
    if (input.size() == 1)
        sorted.push_back(input.front());
    else
    {
        makePairs();
        sortPairs();
        SortMergePairs(pairs, 0, pairs.size() - 1);
        splitSortedPending();
        doInsertOrder();
        insertPend();
    }
}

void PmergeMe::FJvector::makePairs()
{
    for (unsigned int i = 0; i + 1 < input.size(); i += 2)
        pairs.push_back(std::make_pair(input[i], input[i + 1]));
    // Debug output
    std::cout << "Initial pairs: ";
    for (std::vector<std::pair<int, int> >::const_iterator it = pairs.begin(); 
         it != pairs.end(); ++it) {
        std::cout << "(" << it->first << ", " << it->second << ") ";
    }
    std::cout << std::endl;
}

void PmergeMe::FJvector::sortPairs()
{
     for (unsigned int i = 0; i < pairs.size(); i++)
    {
        if (pairs[i].first > pairs[i].second)
            std::swap(pairs[i].first, pairs[i].second);
    }
    // Debug output
    std::cout << "Pairs after sort: ";
    for (std::vector<std::pair<int, int> >::const_iterator it = pairs.begin(); 
         it != pairs.end(); ++it) {
        std::cout << "(" << it->first << ", " << it->second << ") ";
    }
    std::cout << std::endl;
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
    SortMergePairs(tab, start, mid);
    SortMergePairs(tab, mid + 1, end);
    mergeSortedPairs(tab, start, mid, end);
}

void PmergeMe::FJvector::splitSortedPending()
{
    // sorted.push_back(pairs[0].first); // smaller one
    for (unsigned int i = 0; i < pairs.size(); i++)
    {
        sorted.push_back(pairs[i].first);
        pending.push_back(pairs[i].second); // bigger to pending
    }
    // Debug: Print sorted and pending
    std::cout << "Sorted initial elements: ";
    for (int s : sorted) std::cout << s << " ";
    std::cout << "\nPending elements: ";
    for (int p : pending) std::cout << p << " ";
    std::cout << std::endl;
}

std::vector<int> PmergeMe::FJvector::generateJacobsthal(int n)
{
    std::vector<int> jacobsthal = {0, 1};

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
    std::vector<int> jacobsthal = generateJacobsthal(pending.size());
    for (unsigned int i = 0; i < jacobsthal.size(); i++)
    {
        int jacob = jacobsthal[i];
        insertOrder.push_back(jacob);
        for (int pos = jacob - 1; pos > lastInsertedNbr; --pos) {
            insertOrder.push_back(pos);
        }
        lastInsertedNbr = jacob;
    }
    std::cout << "\nJacobsthal insert order: ";
    for (int j : insertOrder) std::cout << j << " ";
    std::cout << std::endl;
}

int PmergeMe::FJvector::binarySearchPos(int pendNum, int start, int end)
{
    int mid = (start + end) / 2;

    if (end <= start)
        return (pendNum > sorted.at(start) ? (start + 1) : start);
    if (pendNum == sorted[mid])
        return (mid + 1);
    if (pendNum > sorted[mid])
        return (binarySearchPos(pendNum, mid + 1, end));
    return (binarySearchPos(pendNum, start, mid - 1));
}

void PmergeMe::FJvector::insertPend()
{
    if (pending.empty() || insertOrder.empty())
        return;

    // int insertTotal = 0;
    for (int pos : insertOrder)
    {
        int val = pending[pos];
        // int end = sorted.size() - 1;
        int insertPos = binarySearchPos(val, 0, sorted.size() - 1);
        sorted.insert(sorted.begin() + insertPos, val);
        // insertTotal++;
    }
    if (input.size() % 2 == 1)
    {
        int val = input.back();
        int insertPos = binarySearchPos(val, 0, sorted.size() - 1);
        sorted.insert(sorted.begin() + insertPos, val);
    }
}

void PmergeMe::FJdeque::parseInput(char **av)
{
    for (unsigned int i = 0; av[i]; i++)
    {
        int num = std::atoi(av[i]);
        if (num <= 0)
        {
            std::cerr << "Error: " << std::endl;
            throw std::invalid_argument("Invalid input!");
        }
        input.push_back(num);
    }
}

void PmergeMe::FJdeque::execFJ(char **av)
{
    // parseInput(av);
    if (input.size() == 1)
        sorted.push_back(input.front());
    else
    {
        makePairs();
        sortPairs();
        SortMergePairs(pairs, 0, pairs.size() - 1);
        splitSortedPending();
        doInsertOrder();
        insertPend();
    }
}

void PmergeMe::FJdeque::makePairs()
{
    for (unsigned int i = 0; i + 1 < input.size(); i += 2)
        pairs.push_back(std::make_pair(input[i], input[i + 1]));
}

void PmergeMe::FJdeque::sortPairs()
{
    for (unsigned int i = 0; i < pairs.size(); i++)
    {
        if (pairs[i].first > pairs[i].second)
            std::swap(pairs[i].first, pairs[i].second);
    }
}

void PmergeMe::FJdeque::mergeSortedPairs(std::deque<std::pair<int, int>>& tab, int start, int mid, int end)
{
    std::deque<std::pair<int, int>> leftArr(tab.begin() + start, tab.begin() + mid + 1);
    std::deque<std::pair<int, int>> rightArr(tab.begin() + mid + 1, tab.begin() + end + 1);
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

void PmergeMe::FJdeque::SortMergePairs(std::deque<std::pair<int, int>>& tab, int start, int end)
{
    int mid = start + (end - start) / 2;
    if (start >= end)
        return;
    SortMergePairs(tab, start, mid);
    SortMergePairs(tab, mid + 1, end);
    mergeSortedPairs(tab, start, mid, end);
}

void PmergeMe::FJdeque::splitSortedPending()
{
    // sorted.push_back(pairs[0].first); // smaller one
    for (unsigned int i = 0; i < pairs.size(); i++)
    {
        sorted.push_back(pairs[i].first);
        pending.push_back(pairs[i].second); // bigger to pending
    }
    // Debug: Print sorted and pending
    std::cout << "Sorted initial elements: ";
    for (int s : sorted) std::cout << s << " ";
    std::cout << "\nPending elements: ";
    for (int p : pending) std::cout << p << " ";
    std::cout << std::endl;
}

std::deque<int> PmergeMe::FJdeque::generateJacobsthal(int n)
{
    std::deque<int> jacobsthal = {0, 1};

    while (jacobsthal.back() < n)
    {
        int next = jacobsthal[jacobsthal.size() - 1] + 2 * jacobsthal[jacobsthal.size() - 2];
        if (next >= n) break;
        jacobsthal.push_back(next);
    }
    return jacobsthal;
}

void PmergeMe::FJdeque::doInsertOrder()
{
    int lastInsertedNbr = 1;
    std::deque<int> jacobsthal = generateJacobsthal(pending.size());
    for (unsigned int i = 0; i < jacobsthal.size(); i++)
    {
        int jacob = jacobsthal[i];
        insertOrder.push_back(jacob);
        for (int pos = jacob - 1; pos > lastInsertedNbr; --pos) {
            insertOrder.push_back(pos);
        }
        lastInsertedNbr = jacob;
    }
}

int PmergeMe::FJdeque::binarySearchPos(int pendNum, int start, int end)
{
    int mid = (start + end) / 2;

    if (end <= start)
        return (pendNum > sorted.at(start) ? (start + 1) : start);
    if (pendNum == sorted[mid])
        return (mid + 1);
    if (pendNum > sorted[mid])
        return (binarySearchPos(pendNum, mid + 1, end));
    return (binarySearchPos(pendNum, start, mid - 1));
}

void PmergeMe::FJdeque::insertPend()
{
    if (pending.empty() || insertOrder.empty())
        return;

    int insertTotal = 0;
    for (int pos : insertOrder)
    {
        int val = pending[pos];
        int end = sorted.size() - 1;
        int insertPos = binarySearchPos(val, 0, end);
        sorted.insert(sorted.begin() + insertPos, val);
        insertTotal++;
    }
    if (input.size() % 2 == 1)
    {
        int val = input.back();
        int insertPos = binarySearchPos(val, 0, sorted.size() - 1);
        sorted.insert(sorted.begin() + insertPos, val);
    }
}

void PmergeMe::runAndTimeVector(char **av)
{
    clock_t start = clock();
    fjv.parseInput(av);
    fjv.execFJ(av);
    clock_t end = clock();
    timeVector = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000.0; // microseconds
}

void PmergeMe::runAndTimeDeque(char **av)
{
    clock_t start = clock();
    fjd.parseInput(av);
    fjd.execFJ(av);
    clock_t end = clock();
    timeDeque = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000.0; // microseconds
}

void PmergeMe::printTimeVector() const
{
    std::cout << "Time to process a range of " << fjv.getSorted().size()
              << " elements with std::vector: "
              << std::fixed << std::setprecision(5) << timeVector << " us" << std::endl;
}

void PmergeMe::printTimeDeque() const
{
    std::cout << "Time to process a range of " << fjd.getSorted().size()
              << " elements with std::deque: "
              << std::fixed << std::setprecision(5) << timeDeque << " us" << std::endl;
}

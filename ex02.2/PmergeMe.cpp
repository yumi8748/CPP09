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
    // std::cout << "Initial pairs: ";
    // for (std::vector<std::pair<int, int> >::const_iterator it = pairs.begin(); 
    //      it != pairs.end(); ++it) {
    //     std::cout << "(" << it->first << ", " << it->second << ") ";
    // }
    // std::cout << std::endl;
}

void PmergeMe::FJvector::sortPairs()
{
     for (unsigned int i = 0; i < pairs.size(); i++)
    {
        if (pairs[i].first < pairs[i].second)
            std::swap(pairs[i].first, pairs[i].second);
    }
    // Debug output
    // std::cout << "Pairs after sort: ";
    // for (std::vector<std::pair<int, int> >::const_iterator it = pairs.begin(); 
    //      it != pairs.end(); ++it) {
    //     std::cout << "(" << it->first << ", " << it->second << ") ";
    // }
    // std::cout << std::endl;
}

void PmergeMe::FJvector::mergeSortedPairs(std::vector<std::pair<int, int>>& tab, int start, int mid, int end)
{
    std::vector<std::pair<int, int>> leftArr(tab.begin() + start, tab.begin() + mid + 1);
    std::vector<std::pair<int, int>> rightArr(tab.begin() + mid + 1, tab.begin() + end + 1);
    unsigned int wholeI = static_cast<unsigned int>(start);
    unsigned int leftI = 0, rightI = 0;

     // Debug: Print initial subarrays
    // std::cout << std::endl;
    // std::cout << "Merging pairs between pairs [" << start << "] and pairs[" << end << "] :\n";
    // std::cout << "Left array: ";
    // for (size_t i = 0; i < leftArr.size(); i++) {
    //     std::cout << "(" << leftArr[i].first << ", " << leftArr[i].second << ") ";
    // }
    // std::cout << "\nRight array: ";
    // for (size_t i = 0; i < rightArr.size(); i++) {
    //     std::cout << "(" << rightArr[i].first << ", " << rightArr[i].second << ") ";
    // }
    // std::cout << std::endl;

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
    // Debug: Print the result of merging
    // std::cout << "After merging: ";
    // for (int i = start; i <= end; ++i) {
    //     std::cout << "(" << tab[i].first << ", " << tab[i].second << ") ";
    // }
    // std::cout << std::endl;
    // std::cout << std::endl;
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
    // std::cout << "Sorted initial elements: ";
    // for (int s : sorted) std::cout << s << " ";
    // std::cout << "\nPending elements: ";
    // for (int p : pending) std::cout << p << " ";
    // std::cout << std::endl;
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

    // std::cout << "\n*Jacobsthal order: ";
    // for (int j : jacobsthal) std::cout << j << " ";
    // std::cout << std::endl;

    for (unsigned int i = 0; i < jacobsthal.size(); i++)
    {
        int jacob = jacobsthal[i];
        insertOrder.push_back(jacob);
        for (int pos = jacob - 1; pos > lastInsertedNbr; --pos) {
            insertOrder.push_back(pos);
        }
        lastInsertedNbr = jacob;
    }
    // std::cout << "\n*Insert order: ";
    // for (int i : insertOrder) std::cout << i << " ";
    // std::cout << std::endl;
}

int PmergeMe::FJvector::binarySearchPos(int pendNum, int start, int end)
{
    int mid = (start + end) / 2;

    if (end <= start)
        return (pendNum > sorted[start]) ? (start + 1) : start;
    if (pendNum == sorted[mid])
        return (mid + 1);
    else if (pendNum > sorted[mid])
        return (binarySearchPos(pendNum, mid + 1, end));
    else
        return (binarySearchPos(pendNum, start, mid - 1));
}

void PmergeMe::FJvector::insertPend()
{
    if (pending.empty() || insertOrder.empty())
        return;

    std::vector<int>::size_type i;
    for (i = 0; i < insertOrder.size(); ++i)
    {
        int pos = insertOrder[i];
        if (pos >= pending.size()) continue; // 防止越界
        
        int val = pending[pos];
        int insertPos = binarySearchPos(val, 0, sorted.size() - 1);
    
        // std::cout << "Inserting " << val << " from pending at position " << pos 
        //           << " into sorted at position " << insertPos << ": ";

        // for (std::vector<int>::const_iterator it = sorted.begin(); it != sorted.end(); ++it)
        //     std::cout << *it << " ";
        // std::cout << std::endl;
        
        sorted.insert(sorted.begin() + insertPos, val);

        // std::cout << "After insertion of " << val << ": ";
        // for (std::vector<int>::const_iterator it = sorted.begin(); it != sorted.end(); ++it)
        //     std::cout << *it << " ";
        // std::cout << std::endl;

        // 移除已插入的元素以防重複
        pending.erase(pending.begin() + pos);

        // std::cout << "Updated pending: ";
        // for (std::vector<int>::const_iterator it = pending.begin(); it != pending.end(); ++it)
        //     std::cout << *it << " ";
        // std::cout << std::endl;

        // 更新插入順序以考慮刪除的元素
        for (std::vector<int>::size_type j = i + 1; j < insertOrder.size(); ++j) {
            if (insertOrder[j] > pos) --insertOrder[j];
            else if (insertOrder[j] == pos) insertOrder[j] = 0;
        }
        // std::cout << "Updated insert order: ";
        // for (std::vector<int>::size_type k = 0; k < insertOrder.size(); ++k)
        //     std::cout << insertOrder[k] << " ";
        // std::cout << std::endl;
    }
    if (input.size() % 2 == 1)
    {
        int val = input.back();
        int insertPos = binarySearchPos(val, 0, sorted.size() - 1);
        sorted.insert(sorted.begin() + insertPos, val);
        // Debug: Show sorted array after inserting the last unpaired element
        // std::cout << "Inserted last unpaired " << val << " at position " << insertPos << ": ";
        // for (int s : sorted) std::cout << s << " ";
        // std::cout << std::endl;
        // std::cout << std::endl;
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
    // Debug output
    // std::cout << "Initial pairs: ";
    // for (std::deque<std::pair<int, int> >::const_iterator it = pairs.begin(); 
    //      it != pairs.end(); ++it) {
    //     std::cout << "(" << it->first << ", " << it->second << ") ";
    // }
    // std::cout << std::endl;
}

void PmergeMe::FJdeque::sortPairs()
{
     for (unsigned int i = 0; i < pairs.size(); i++)
    {
        if (pairs[i].first > pairs[i].second)
            std::swap(pairs[i].first, pairs[i].second);
    }
    // Debug output
    // std::cout << "Pairs after sort: ";
    // for (std::deque<std::pair<int, int> >::const_iterator it = pairs.begin(); 
    //      it != pairs.end(); ++it) {
    //     std::cout << "(" << it->first << ", " << it->second << ") ";
    // }
    // std::cout << std::endl;
}

void PmergeMe::FJdeque::mergeSortedPairs(std::deque<std::pair<int, int>>& tab, int start, int mid, int end)
{
    std::deque<std::pair<int, int>> leftArr(tab.begin() + start, tab.begin() + mid + 1);
    std::deque<std::pair<int, int>> rightArr(tab.begin() + mid + 1, tab.begin() + end + 1);
    unsigned int wholeI = static_cast<unsigned int>(start);
    unsigned int leftI = 0, rightI = 0;

     // Debug: Print initial subarrays
    // std::cout << std::endl;
    // std::cout << "Merging pairs between pairs [" << start << "] and pairs[" << end << "] :\n";
    // std::cout << "Left array: ";
    // for (size_t i = 0; i < leftArr.size(); i++) {
    //     std::cout << "(" << leftArr[i].first << ", " << leftArr[i].second << ") ";
    // }
    // std::cout << "\nRight array: ";
    // for (size_t i = 0; i < rightArr.size(); i++) {
    //     std::cout << "(" << rightArr[i].first << ", " << rightArr[i].second << ") ";
    // }
    // std::cout << std::endl;

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
    // Debug: Print the result of merging
    // std::cout << "After merging: ";
    // for (int i = start; i <= end; ++i) {
    //     std::cout << "(" << tab[i].first << ", " << tab[i].second << ") ";
    // }
    // std::cout << std::endl;
    // std::cout << std::endl;
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
    // std::cout << "Sorted initial elements: ";
    // for (int s : sorted) std::cout << s << " ";
    // std::cout << "\nPending elements: ";
    // for (int p : pending) std::cout << p << " ";
    // std::cout << std::endl;
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

    // std::cout << "\nJacobsthal order: ";
    // for (int j : jacobsthal) std::cout << j << " ";
    // std::cout << std::endl;

    for (unsigned int i = 0; i < jacobsthal.size(); i++)
    {
        int jacob = jacobsthal[i];
        insertOrder.push_back(jacob);
        for (int pos = jacob - 1; pos > lastInsertedNbr; --pos) {
            insertOrder.push_back(pos);
        }
        lastInsertedNbr = jacob;
    }
    // std::cout << "\nInsert order: ";
    // for (int i : insertOrder) std::cout << i << " ";
    // std::cout << std::endl;
}

int PmergeMe::FJdeque::binarySearchPos(int pendNum, int start, int end)
{
    int mid = (start + end) / 2;

    if (end <= start)
        return (pendNum > sorted[start]) ? (start + 1) : start;
    if (pendNum == sorted[mid])
        return (mid + 1);
    else if (pendNum > sorted[mid])
        return (binarySearchPos(pendNum, mid + 1, end));
    else
        return (binarySearchPos(pendNum, start, mid - 1));
}

void PmergeMe::FJdeque::insertPend()
{
    if (pending.empty() || insertOrder.empty())
        return;

    std::deque<int>::size_type i;
    for (i = 0; i < insertOrder.size(); ++i)
    {
        int pos = insertOrder[i];
        if (pos >= pending.size()) continue; // 防止越界
        
        int val = pending[pos];
        int insertPos = binarySearchPos(val, 0, sorted.size() - 1);

        // std::cout << "Inserting " << val << " from pending at position " << pos 
        //           << " into sorted at position " << insertPos << ": ";

        // for (std::deque<int>::const_iterator it = sorted.begin(); it != sorted.end(); ++it)
        //     std::cout << *it << " ";
        // std::cout << std::endl;
        
        sorted.insert(sorted.begin() + insertPos, val);

        // std::cout << "After insertion of " << val << ": ";
        // for (std::deque<int>::const_iterator it = sorted.begin(); it != sorted.end(); ++it)
        //     std::cout << *it << " ";
        // std::cout << std::endl;

        // 移除已插入的元素以防重複
        pending.erase(pending.begin() + pos);

        // std::cout << "Updated pending: ";
        // for (std::deque<int>::const_iterator it = pending.begin(); it != pending.end(); ++it)
        //     std::cout << *it << " ";
        // std::cout << std::endl;

        // 更新插入順序以考慮刪除的元素
        for (std::deque<int>::size_type j = i + 1; j < insertOrder.size(); ++j) {
            if (insertOrder[j] > pos) --insertOrder[j];
        }
        // std::cout << "Updated insert order: ";
        // for (std::deque<int>::size_type k = 0; k < insertOrder.size(); ++k)
        //     std::cout << insertOrder[k] << " ";
        // std::cout << std::endl;
    }
    if (input.size() % 2 == 1)
    {
        int val = input.back();
        int insertPos = binarySearchPos(val, 0, sorted.size() - 1);
        sorted.insert(sorted.begin() + insertPos, val);
        // Debug: Show sorted array after inserting the last unpaired element
        // std::cout << "Inserted last unpaired " << val << " at position " << insertPos << ": ";
        // for (int s : sorted) std::cout << s << " ";
        // std::cout << std::endl;
        // std::cout << std::endl;
    }
}

void PmergeMe::runAndTimeVector(char **av)
{
    clock_t start = clock();
    fjv.parseInput(av);
    fjv.execFJ(av);
    clock_t end = clock();
    timeVector = static_cast<double>(end - start) / CLOCKS_PER_SEC;
}

void PmergeMe::runAndTimeDeque(char **av)
{
    clock_t start = clock();
    fjd.parseInput(av);
    fjd.execFJ(av);
    clock_t end = clock();
    timeDeque = static_cast<double>(end - start) / CLOCKS_PER_SEC;
}

void PmergeMe::printTimeVector() const
{
    std::cout << "Time to process a range of " << fjv.getSorted().size()
              << " elements with std::vector: "
              << std::fixed << std::setprecision(5) << timeVector << " seconds" << std::endl;
}

void PmergeMe::printTimeDeque() const
{
    std::cout << "Time to process a range of " << fjd.getSorted().size()
              << " elements with std::deque: "
              << std::fixed << std::setprecision(5) << timeDeque  << " seconds" << std::endl;
}

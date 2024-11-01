#include "PmergeMe.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/
PmergeMe::PmergeMe(): timeVector(0), timeDeque(0)
{
}

PmergeMe::PmergeMe( const PmergeMe & src ): vec(src.vec), deq(src.deq), timeVector(src.timeVector), timeDeque(src.timeDeque)
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
PmergeMe &	PmergeMe::operator=( PmergeMe const & src )
{
	if ( this != &src )
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
	for(int i = 1; av[i]; i++) //++i?
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

void	PmergeMe::sortVector()
{
	std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
	mergeInsertSort(vec);
	std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
	timeVector = std::chrono::duration<double, std::micro>(end - start).count();
}

void	PmergeMe::sortDeque()
{
	std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
	mergeInsertSort(deq);
	std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
	timeDeque = std::chrono::duration<double, std::micro>(end - start).count();
}

void	PmergeMe::printUnsorted() const
{
	std::cout << "Before: " << std::endl;
	for (std::vector<int>::const_iterator it = vec.begin(); it != vec.end(); it++) //++it?
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

void	PmergeMe::printSorted() const
{
	std::cout << "After: " << std::endl;
	for (std::vector<int>::const_iterator it = vec.begin(); it != vec.end(); it++) //++it?
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

void	PmergeMe::printTimeVector() const
{
	std::cout << "Time to process a range of " << vec.size()
		<< " elements with std::vector: " 
		<< std::fixed << std::setprecision(5) << timeVector << " us" << std::endl;
}

void	PmergeMe::printTimeDeque() const
{
	std::cout << "Time to process a range of " << deq.size()
		<< " elements with std::deque: " 
		<< std::fixed << std::setprecision(5) << timeDeque << " us" << std::endl;
}

std::vector<int> PmergeMe::getJacobsthal(int n)
{
	// std::vector<int> sequence;
    // int j1 = 0, j2 = 1;

    // while (j2 <= n)
	// {
    //     sequence.push_back(j2);
    //     int j_next = j2 + 2 * j1;
    //     j1 = j2;
    //     j2 = j_next;
	// }
	// return sequence;

	std::vector<int> sequence;
    
    // 生成 Jacobsthal 數列直到不超過 n
    int j0 = 0; // J(0)
    int j1 = 1; // J(1)

    if (n >= j0) sequence.push_back(j0); // 如果 n >= J(0)，則添加 J(0)
    if (n >= j1) sequence.push_back(j1); // 如果 n >= J(1)，則添加 J(1)

    // 使用迴圈計算後續的 Jacobsthal 數
    int j_next;
    for (int i = 2; ; i++) {
        j_next = j1 + 2 * j0; // J(n) = J(n-1) + 2 * J(n-2)
        if (j_next > n) break; // 如果超過 n，就停止
        sequence.push_back(j_next); // 添加到序列中

        // 更新 j0 和 j1
        j0 = j1;
        j1 = j_next;
    }
    
    return sequence;
}

template <typename T>
void PmergeMe::execInsert(T& sorted, const T& tmp) {
    std::vector<int> jacobSeq = getJacobsthal(tmp.size());

    // for (std::vector<int>::const_iterator it = jacobSeq.begin(); it != jacobSeq.end(); ++it) {
    //     if (*it < tmp.size()) {
    //         int value = tmp[*it];
    //         typename T::iterator pos = std::lower_bound(sorted.begin(), sorted.end(), value);
    //         sorted.insert(pos, value);
    //     }
    // }
	// for (const int& index : jacobSeq)
	// {
    //     if (index < tmp.size()) {
    //         int value = tmp[index];
    //         typename T::iterator pos = std::lower_bound(sorted.begin(), sorted.end(), value);
    //         sorted.insert(pos, value);
    //     }
    // }
	for (size_t i = 0; i < tmp.size(); ++i) {
        int value = tmp[i];
        typename T::iterator pos = std::lower_bound(sorted.begin(), sorted.end(), value);
        sorted.insert(pos, value);
    }
}

void PmergeMe::mergeInsertSort(std::vector<int>& container)
{
	if (container.size() <= 1 )
		return ;

	std::vector<int>sorted;
	std::vector<int>tmp;
	for (int i = 0; i < container.size(); i += 2)
	{
		if (i + 1 < container.size())
		{
			if (container[i] < container[i + 1])
			{
				sorted.push_back(container[i]); //small one
				tmp.push_back(container[i + 1]);
			}
			else
			{
				sorted.push_back(container[i + 1]); //small one
				tmp.push_back(container[i]);
			}
		}
		else
			sorted.push_back(container[i]);
	}
	std::sort(sorted.begin(), sorted.end());
	execInsert(sorted, tmp);
	// for (std::vector<int>::iterator it = tmp.begin(); it != tmp.end(); it++) //++it?
	// {
	// 	//to check
	// 	std::vector<int>::iterator pos = std::lower_bound(sorted.begin(), sorted.end(), *it);
	// 	sorted.insert(pos, *it);
	// }
	container = sorted;
}

void PmergeMe::mergeInsertSort(std::deque<int>& container)
{
	if (container.size() <= 1)
		return ;
	
	std::deque<int> sorted;
	std::deque<int> tmp;
	for (int i = 0; i < container.size(); i += 2)
	{
		if (i + 1 < container.size())
		{
			if (container[i] < container[i + 1])
			{
				sorted.push_back(container[i]);
				tmp.push_back(container[i + 1]);
			}
			else
			{
				sorted.push_back(container[i + 1]);
				tmp.push_back(container[i]);
			}
		}
		else
			sorted.push_back(container[i]);
	}
	std::sort(sorted.begin(), sorted.end());
	execInsert(sorted, tmp);
	// for (std::deque<int>::iterator it = tmp.begin(); it != tmp.end(); it++)
	// {
	// 	std::deque<int>::iterator pos = std::lower_bound(sorted.begin(), sorted.end(), *it); //Returns an iterator pointing to the first element in the range [first,last) which does not compare less than val.
	// 	sorted.insert(pos, *it);
	// }
	container = sorted;
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/


/* ************************************************************************** */
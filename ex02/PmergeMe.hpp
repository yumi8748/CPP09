#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <iostream>
# include <string>
# include <vector>
# include <deque>
# include <chrono>
# include <algorithm>
# include <iomanip>


class PmergeMe
{
	public:
		PmergeMe();
		PmergeMe(PmergeMe const & src);
		~PmergeMe();
		PmergeMe(char *av[]);
		PmergeMe & operator=(PmergeMe const & src);

		void parseInput(char *av[]);
		void sortVector();
		void sortDeque();
		void printUnsorted() const;
		void printSorted() const;
		void printTimeVector() const;
		void printTimeDeque() const;

	private:
		std::vector<int> vec;
		std::deque<int> deq;
		double timeVector;
        double timeDeque;

		// Merge-Insert Sort 的模板函數
		template <typename T>
		void mergeInsertSort(T& container);

		// 插入排序輔助函數的模板函數
		template <typename T>
		void execInsert(T& sorted, const T& tmp);

		// 計算 Jacobsthal 數列的函數
		std::vector<int> getJacobsthal(int n);
};

#endif /* ******************************************************** PMERGEME_H */
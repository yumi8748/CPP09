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
		PmergeMe( PmergeMe const & src );
		~PmergeMe();
		PmergeMe(char *av[]);
		PmergeMe &		operator=( PmergeMe const & src );

		void	parseInput(char *av[]);
		void	sortVector();
		void	sortDeque();

		void	printUnsorted() const;
		void	printSorted() const;
		void	printTimeVector() const;
		void	printTimeDeque() const;

	private:
		std::vector<int> vec;
		std::deque<int> deq;
		double timeVector;
        double timeDeque;

        void mergeInsertSort(std::vector<int>& container);
        void mergeInsertSort(std::deque<int>& container);
		std::vector<int> getJacobsthal(int n);
		template <typename T>
    	void execInsert(T& sorted, const T& tmp);
};

#endif /* ******************************************************** PMERGEME_H */
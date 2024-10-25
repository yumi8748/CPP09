#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <iostream>
# include <string>
# include <vector>
# include <deque>

template <typename T>
class PmergeMe
{

	public:

		PmergeMe();
		PmergeMe( PmergeMe const & src );
		~PmergeMe();
		PmergeMe(char *av[]);
		PmergeMe &		operator=( PmergeMe const & rhs );

		void	parseInput(const);
		void	sortVector();
		void	sortDeque();

		void	printUnsorted() const;
		void	printSorted() const;
		void	printTimeVector() const;
		void	printTimeDeque() const;

	private:
		std::vector<int> vec;
		std::deque<int> deq;

};


#endif /* ******************************************************** PMERGEME_H */
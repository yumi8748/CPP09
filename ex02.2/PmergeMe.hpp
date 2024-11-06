#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <iostream>
# include <string>
# include <vector>
# include <deque>
# include <chrono>
# include <algorithm>
#include <utility> //std::pair

class PmergeMe
{
	public:
		PmergeMe();
		PmergeMe(PmergeMe const & src);
		~PmergeMe();
		PmergeMe & operator=(PmergeMe const & src);

		void printUnsorted() const;
		void printSorted() const;

		class FJvector{
			public:
				FJvector();
				FJvector(FJvector const & src);
				~FJvector();
				FJvector & operator=(FJvector const & src);

				void	execFJ(char **av);

			private:
				std::vector<int> input;
				std::vector<std::pair<int, int> > pairs;
				std::vector<int> sorted;
				std::vector<int> pending;
				std::vector<int> insertOrder;

				void parseInput(char **av);
				void makePairs();
				void sortPairs();
				void SortMergeParis(std::vector<std::pair<int, int> > &tab, int start, int end);
				void merge(std::vector<std::pair<int, int> > &tab, int start, int mid, int end);
				void splitSortedPending();
				void doInsertOrder();
				int binarySearchPos(int pendNum, int start, int end);
				void insertPend();
		};

		class FJdeque{
			public:
				FJdeque();
				FJdeque(FJdeque const & src);
				~FJdeque();
				FJdeque & operator=(FJdeque const & src);

				void	execFJ(char **av);

			private:
				std::deque<int> input;
				std::deque<std::pair<int, int> > pairs;
				std::deque<int> sorted;
				std::deque<int> pending;
				std::deque<int> insertOrder;

				void parseInput(char **av);
				void makePairs();
				void sortPairs();
				void SortMergeParis(std::deque<std::pair<int, int> > &tab, int start, int end);
				void merge(std::deque<std::pair<int, int> > &tab, int start, int mid, int end);
				void splitSortedPending();
				void doInsertOrder();
				int binarySearchPos(int pendNum, int start, int end);
				void insertPend();
		};
};

#endif /* ******************************************************** PMERGEME_H */
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

		void printTimeVector() const;
		void printTimeDeque() const;
		void printUnsorted() const;
       	void printSorted() const;

		class FJvector{
			public:
				FJvector();
				FJvector(FJvector const & src);
				~FJvector();
				FJvector & operator=(FJvector const & src);

				void	execFJ(char **av);
				void parseInput(char **av);
				void makePairs();
				void sortPairs();
				void SortMergePairs(std::vector<std::pair<int, int> > &tab, int start, int end);
				void mergeSortedPairs(std::vector<std::pair<int, int> > &tab, int start, int mid, int end);
				void splitSortedPending();
				void doInsertOrder();
				std::vector<int> generateJacobsthal(int n);
				int binarySearchPos(int pendNum, int start, int end);
				void insertPend();
				const std::vector<int>& getInput() const { return input; }
				const std::vector<int>& getSorted() const { return sorted; }

			private:
				std::vector<int> input;
				std::vector<std::pair<int, int> > pairs;
				std::vector<int> sorted;
				std::vector<int> pending;
				std::vector<int> insertOrder;
		};

		class FJdeque{
			public:
				FJdeque();
				FJdeque(FJdeque const & src);
				~FJdeque();
				FJdeque & operator=(FJdeque const & src);

				void	execFJ(char **av);
				const std::deque<int>& getInput() const { return input; }
				const std::deque<int>& getSorted() const { return sorted; }
				void parseInput(char **av);
				void makePairs();
				void sortPairs();
				void SortMergePairs(std::deque<std::pair<int, int> > &tab, int start, int end);
				void mergeSortedPairs(std::deque<std::pair<int, int> > &tab, int start, int mid, int end);
				void splitSortedPending();
				void doInsertOrder();
				std::deque<int> generateJacobsthal(int n);
				int binarySearchPos(int pendNum, int start, int end);
				void insertPend();

			private:
				std::deque<int> input;
				std::deque<std::pair<int, int> > pairs;
				std::deque<int> sorted;
				std::deque<int> pending;
				std::deque<int> insertOrder;
		};

		void runAndTimeVector(char **av);
		void runAndTimeDeque(char **av);

	private:
		FJvector fjv;
		FJdeque fjd;
		double timeVector = 0.0;
		double timeDeque = 0.0;
};

#endif /* ******************************************************** PMERGEME_H */
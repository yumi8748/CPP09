#include "PmergeMe.hpp"

int main(int ac, char *av[])
{
	if (ac < 2)
	{
		std::cerr << "Error: input required!" << std::endl;
		return 1;
	}
	PmergeMe sorter(av);
	
	sorter.printUnsorted();
	sorter.sortVector();
	sorter.sortDeque();
	sorter.printSorted();
	sorter.printTimeVector();
	sorter.printTimeDeque();

	return 0;
}
#include "PmergeMe.hpp"

int	main(int ac, char *av[])
{
	if (ac < 2)
	{
		std::cerr << "Error: input required!" << std::endl;
		return (1);
	}
	try{
		std::vector<std::string>;

	}catch(std::exception &e){
		std::cerr << e.what() << std::endl;
		return (1);
	}
	std::cout << "Before: " << std::endl;
	std::cout << "After: " << std::endl;
	std::cout << "Time used to process with vector: " << std::endl;
	std::cout << "Time used to process with deque: " << std::endl;
	return (0);
}
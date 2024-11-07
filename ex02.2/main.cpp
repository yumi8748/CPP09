#include "PmergeMe.hpp"

int main(int ac, char **av)
{
	if (ac < 2)
	{
		std::cerr << "Error: input required!" << std::endl;
		return 1;
	}
    try{
        av++;  // 跳過程式名稱
        PmergeMe pmm;

        pmm.printUnsorted();
        
        // 計時並顯示 `std::vector` 的處理時間
        pmm.runAndTimeVector(av);
        pmm.printSorted();
        pmm.printTimeVector();

        // 計時並顯示 `std::deque` 的處理時間
        // pmm.runAndTimeDeque(av);
        // pmm.printTimeDeque();

        return 0;

    } catch (std::invalid_argument &e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
}
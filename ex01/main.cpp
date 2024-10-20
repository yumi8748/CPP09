# include "RPN.hpp"

int main(int ac, char **av)
{
    if (ac != 2)
    {
        std::cerr << "Error: incorrect number of arguments." << std::endl;
        return (1);
    }
    try{
        int res = evaluate_rpn(av[1]);
        std::cout << res << std::endl;
    }catch(std::exception &e){
        std::cerr << e.what() << std::endl;
        return (1);
    }
    return (0);
}
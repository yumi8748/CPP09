#ifndef RPN_HPP
# define RPN_HPP

# include <iostream>
# include <string>
# include <sstream>
# include <stack>
# include <cstdlib>

class RPN
{
	public:
		RPN();
		RPN( RPN const & src );
		~RPN();

		RPN &		operator=( RPN const & rhs );
		static int	evaluate_rpn(const std::string &input); //purely static class, cannot be instantiated. This design choice aligns with most C++ math libraries, which consist of static functions offering methods for trigonometry, statistics, and other mathematical operations without needing an object.

	private:
		static bool isNumber(const std::string &token);
		static bool isOperator(const std::string &token);
		static int calculation(int v1, int v2, std::string &oper);
};

#endif /* ************************************************************* RPN_H */
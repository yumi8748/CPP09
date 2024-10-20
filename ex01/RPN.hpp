#ifndef RPN_HPP
# define RPN_HPP

# include <iostream>
# include <string>
# include <sstream>
# include <stack>

class RPN
{

	public:

		RPN();
		RPN( RPN const & src );
		~RPN();

		RPN &		operator=( RPN const & rhs );
		int	evaluate_rpn(std::string &token);
	private:
		bool isNumber(const std::string &token);
		bool isOperator(const std::string &input);
		int calculation(int v1, int v2, std::string &oper);
};

#endif /* ************************************************************* RPN_H */
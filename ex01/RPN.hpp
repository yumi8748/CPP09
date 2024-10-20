#ifndef RPN_HPP
# define RPN_HPP

# include <iostream>
# include <string>
# include <sstream>

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
		
};

#endif /* ************************************************************* RPN_H */
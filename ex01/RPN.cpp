#include "RPN.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

RPN::RPN()
{
}

RPN::RPN( const RPN & src )
{
}


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

RPN::~RPN()
{
}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

RPN &				RPN::operator=( RPN const & rhs )
{
	//if ( this != &rhs )
	//{
		//this->_value = rhs.getValue();
	//}
	return *this;
}



/*
** --------------------------------- METHODS ----------------------------------
*/

int RPN::calculation(int v1, int v2, std::string &oper)
{
	if (oper == "+")
		return (v1 + v2);
	if (oper == "-")
		return (v1 - v2);
	if (oper == "/")
	{
		if (v2 == 0)
			throw (std::runtime_error("Error: divided by 0 not allowed."));
		return (v1 / v2);
	}
	if (oper == "*")
		return (v1 * v2);
	throw (std::runtime_error("Error: unknown operator."));
}

bool RPN::isNumber(const std::string &token)
{
	if (token.size() == 1 && isdigit(token[0]))
		return (true);
	return (false);
}

bool RPN::isOperator(const std::string &token)
{
	if (token == "+" || token == "-" || token == "/" || token == "*")
		return (true);
	return (false);
}

int	RPN::evaluate_rpn(std::string &input)
{
	std::istringstream ss(input);
	std::string token;
	std::stack<int> values; //stack

	while (ss >> token)
	{
		if (std::isdigit(token[0])) //0-9
			values.push(std::atoi(token.c_str()));
		else if (isOperator(token))
		{
			if (values.size() < 2)
				std::cerr << ("Error:　insufficient values for operation.") << std::endl;
			int v2 = values.top(); values.pop();
			int v1 = values.top(); values.pop();
			int res = calculation(v1, v2, token); //continue here
		}
	}

}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/


/* ************************************************************************** */
#include "RPN.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

RPN::RPN()
{
}

RPN::RPN( const RPN & src )
{
	*this = src;
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
	if ( this != &rhs )
	{
		return *this;
	}
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

int	RPN::evaluate_rpn(const std::string &input)
{
	std::istringstream ss(input);
	std::string token;
	std::stack<int> values; //stack

	while (ss >> token)
	{
		if (isNumber(token)) //0-9
			values.push(std::atoi(token.c_str()));
		else if (isOperator(token))
		{
			if (values.size() < 2)
				throw (std::runtime_error("Error:　insufficient values for operation."));
			int v2 = values.top(); values.pop();
			int v1 = values.top(); values.pop();
			int res = calculation(v1, v2, token);
			values.push(res);
		}
		else
			throw (std::runtime_error("Error: invalid input."));
	}
	if (values.size() != 1)
		throw (std::runtime_error("Error: invalid input."));
	return (values.top());
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/


/* ************************************************************************** */
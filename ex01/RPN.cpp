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

bool isNumber(const std::string &token)
{
	if (token.size() == 1 && isdigit(token[0]))
		return (true);
	return (false);
}

bool isOperator(const std::string &token)
{
	if (token == "+" || token == "-" || token == "/" || token == "*")
		return (true);
	return (false);
}

int	evaluate_rpn(std::string &input)
{
	std::istringstream ss(input);
	std::string tokens;
	//stack

	while (ss >> tokens)
	{
		if (std::isdigit(tokens[0])) //0-9
			
	}

}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/


/* ************************************************************************** */
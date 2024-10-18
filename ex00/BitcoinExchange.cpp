#include "BitcoinExchange.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

BitcoinExchange::BitcoinExchange()
{
}

BitcoinExchange::BitcoinExchange( const BitcoinExchange & other ): exchangeRate(other.exchangeRate)
{
}

BitcoinExchange::BitcoinExchange(const std::string &fileName){
	loadFile(fileName);
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

BitcoinExchange::~BitcoinExchange()
{
}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

BitcoinExchange &				BitcoinExchange::operator=( BitcoinExchange const & other )
{
	if ( this != &other )
	{
		this->exchangeRate = other.exchangeRate;
	}
	return *this;
}


/*
** --------------------------------- METHODS ----------------------------------
*/
float BitcoinExchange::getExchangeRate(const std::string &date) const{					//map>
	std::map<std::string, float>::const_iterator it = exchangeRate.lower_bound(date); //lower_bound>Returns an iterator pointing to the first element in the range
	if (it == exchangeRate.end() || it->first != date)
	{
		if (it == exchangeRate.begin())
			throw (std::runtime_error("No available exchange rate for this date!"));
		--it; //get closest earlier date
	}
	return (it->second);
}

void	BitcoinExchange::loadFile(const std::string &fileName)
{
	std::ifstream file(fileName.c_str());
	if (!file.is_open())
		throw (std::runtime_error("File cannot be opened!"));

	std::string	line;
	while (std::getline(file, line))
	{
		//check date format??
		std::istringstream ss(line);
		std::string date, rate;
		if (std::getline(ss, date, ',') && std::getline(ss, rate))
			exchangeRate[date] = std::atof(rate.c_str());
	}
	file.close();
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/


/* ************************************************************************** */
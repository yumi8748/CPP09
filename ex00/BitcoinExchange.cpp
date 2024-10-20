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
	std::map<std::string, float>::const_iterator it = exchangeRate.lower_bound(date); //lower_bound>it returns an iterator to the first element that is greater than or equal to the given key.
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

bool BitcoinExchange::check_date(const std::string &date)
{
	if (date.size() != 10 || date[4] != '-' || date[7] != '-') {
        return false;
    }

    int year = std::atoi(date.substr(0, 4).c_str());
    int month = std::atoi(date.substr(5, 2).c_str());
    int day = std::atoi(date.substr(8, 2).c_str());

    if (year < 1000 || year > 9999) {
        return false;
    }
    if (month < 1 || month > 12) {
        return false;
    }

    int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // check leap year
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        days_in_month[1] = 29;
    }

    if (day < 1 || day > days_in_month[month - 1]) {
        return false;
    }

    return true;
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/


/* ************************************************************************** */
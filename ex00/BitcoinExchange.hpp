#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <iostream>
# include <string>
# include <map>
# include <fstream>
# include <sstream>
# include <limits>

class BitcoinExchange
{

	public:

		BitcoinExchange();
		BitcoinExchange( BitcoinExchange const & other );
		~BitcoinExchange();
		BitcoinExchange &		operator=( BitcoinExchange const & other );

		BitcoinExchange(const std::string &file);
		float getExchangeRate(const std::string &date) const;
		bool check_date(const std::string &date);
	
	private:

		std::map<std::string, float> exchangeRate;
		void	loadFile(const std::string &file);

};

#endif /* ************************************************* BITCOINEXCHANGE_H */
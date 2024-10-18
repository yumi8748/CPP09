# include "BitcoinExchange.hpp"

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "Error: incorrect number of arguments." << std::endl;
        return 1;
    }

    try {
        BitcoinExchange exchange("bitcoin_data.csv");

        std::ifstream inputFile(argv[1]);
        if (!inputFile.is_open()) {
            std::cerr << "Error: could not open file." << std::endl;
            return 1;
        }

        std::string line;
        while (std::getline(inputFile, line)) {
            std::istringstream ss(line);
            std::string date, valueStr;
            if (std::getline(ss, date, '|') && std::getline(ss, valueStr)) {
                float value = std::atof(valueStr.c_str());
                if (value < 0 || value > 1000) {
                    std::cerr << "Error: invalid value: " << value << std::endl;
                    continue;
                }
                float rate = exchange.getExchangeRate(date);
                std::cout << date << " => " << value << " = " << value * rate << std::endl;
            } else {
                std::cerr << "Error: invalid input format." << std::endl;
            }
        }
        inputFile.close();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
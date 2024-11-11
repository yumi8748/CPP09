# include "BitcoinExchange.hpp"

int main(int ac, char **av) {
    if (ac != 2) {
        std::cerr << "Error: incorrect number of arguments." << std::endl;
        return 1;
    }

    try {
        BitcoinExchange exchange("data.csv");

        std::ifstream inputFile(av[1]);
        if (!inputFile.is_open()) {
            std::cerr << "Error: could not open file." << std::endl;
            return 1;
        }
        char c;
    if (!(inputFile >> c)) {
        std::cerr << "Error: no permission to read file or file is empty." << std::endl;
        return 1;
    }

        std::string line;
        while (std::getline(inputFile, line)) {
            std::istringstream ss(line);
            std::string date, valueStr;

            // 確保正確格式 (date | value)
            if (std::getline(ss, date, '|') && std::getline(ss, valueStr)) {
                date.erase(date.find_last_not_of(" \n\r\t") + 1); // 去除日期尾部空白
                valueStr.erase(0, valueStr.find_first_not_of(" \n\r\t")); // 去除數值前的空白
                
                // 確認日期格式是否正確
                if (exchange.check_date(date)) {
                    float value = std::atof(valueStr.c_str());
                    
                    // 確認 value 是否在有效範圍內
                    if (value < 0 || value > 1000) {
                        std::cerr << "Error: invalid value: " << value << std::endl;
                        continue;
                    }
                    
                    // 獲取對應日期的匯率並計算
                    float rate = exchange.getExchangeRate(date);
                    std::cout << date << " => " << value << " = " << value * rate << std::endl;
                } else {
                    std::cerr << "Error: invalid date format => " << date << std::endl;
                }
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

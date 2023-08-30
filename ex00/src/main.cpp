#include "BitcoinExchange.hpp"
#include <iostream>

int main() {
	BitcoinExchange btcex;
	struct tm date;
	date.tm_year = 2002;
	date.tm_mon = 5;
	date.tm_mday = 15;
	btcex.add(date, 12);
	std::cout << btcex.search(date) << std::endl;
	date.tm_year = 2002;
	date.tm_mon = 8;
	date.tm_mday = 31;
	std::cout << btcex.search(date) << std::endl;
	date.tm_year = 2001;
	date.tm_mon = 8;
	date.tm_mday = 31;
	std::cout << btcex.search(date) << std::endl;
}

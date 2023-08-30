#include "BitcoinExchange.hpp"
#include <iostream>
#include <cstdlib>
#include <fstream>

std::ostream &operator<<(std::ostream &os, struct tm date) {
	os << date.tm_year + 1900 << "-" << date.tm_mon + 1 << '-' << date.tm_mday;
	return (os);
}

int main(int ac, char **av) {
	BitcoinExchange btcex;
	struct tm date;
	float value, btc;
	std::ifstream file;
	std::string line;

	if (ac < 2) {
		std::cerr << "Error: need a file as argument" << std::endl;
		exit(0);
	}

	file.open("data.csv");
	if (!file.is_open()) {
		std::cerr << "Error: could not open data.csv\n";
		exit(0);
	}
	if (file.good()) std::getline(file, line);
	while (file.good()) {
		std::getline(file, line);
		if(!line.empty()) {
			char *tmp = strptime(line.c_str(), "%Y-%m-%d,", &date);
			if (!tmp) {
				std::cerr << "Error: invalid data.csv\n" << std::endl;
				exit(0);
			}
			value = strtof(tmp, 0);
			btcex.add(date, value);
		}
	}
	file.close();

	file.open(av[1]);
	if (!file.is_open()) {
		std::cerr << "Error: could not open file\n";
		exit(0);
	}
	if (file.good()) {
		std::getline(file, line);
		if (line != "date | value") {
			std::cerr << "Error: wrong input format\n";
			return 0;
		}
	}
	while (file.good()) {
		std::getline(file, line);
		if(!line.empty()) {
			char *tmp = strptime(line.c_str(), "%Y-%m-%d | ", &date);
			if (!tmp || *tmp) {
				std::cerr << "Error: bad input => " << line << std::endl;
				continue;
			}
			btc = strtof(tmp, 0);
			if (btc < 0)
				std::cerr << "Error: not a positive number\n";
			else if (btc > 1000)
				std::cerr << "Error: too large a number\n";
			else {
				value = btcex.search(date);
				if (value < 0)
					std::cerr << "Error: no value at this date\n";
				else
					std::cout << date << " => " << btc << " = " << value * btc << std::endl;
			}
		}
	}
	file.close();
}

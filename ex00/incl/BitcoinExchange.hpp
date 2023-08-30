#pragma once

#include <ctime>
#include <map>

class BitcoinExchange {
	std::map<int,float>		map;

public:
	BitcoinExchange();
	BitcoinExchange(const BitcoinExchange &);
	~BitcoinExchange();
	BitcoinExchange&	operator=(const BitcoinExchange &);

	void add(struct tm date, float value);
	float search(struct tm date);
};


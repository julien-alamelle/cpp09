#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange():map() {}
BitcoinExchange::BitcoinExchange(const BitcoinExchange &src):map(src.map) {}
BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange&	BitcoinExchange::operator=(const BitcoinExchange &src) {
	if (this == &src) return (*this);
	this->map = src.map;
	return (*this);
}

static int tmtoi(struct tm date) {
	if (date.tm_year < 2000) return 33;
	if (date.tm_year > 2063) return (63 << 9) + (12 << 5) + 31;
	return (date.tm_year << 9) + (date.tm_mon << 5) + date.tm_mday;
}

//static struct tm itotm(int i)

void BitcoinExchange::add(struct tm date, float value) {
	this->map.insert(std::pair<int,float>(tmtoi(date), value));
}

float BitcoinExchange::search(struct tm date) {
	int d = tmtoi(date);
	std::map<int,float>::iterator it, tmp;
	it = this->map.find(d);
	if (it != this->map.end()) return (it->second);
	this->map.insert(std::pair<int,float>(d, -1));
	it = this->map.find(d);
	tmp = it;
	float ret = it->second;
	if (it != this->map.begin())
		ret = (--tmp)->second;
	this->map.erase(it);
	return ret;
}

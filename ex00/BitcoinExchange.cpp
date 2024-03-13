/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:46:04 by mmarcott          #+#    #+#             */
/*   Updated: 2024/03/12 21:59:28 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

bool	Dates::operator==(const Dates &rhs) const {
	return (year == rhs.year && month == rhs.month && day == rhs.day);
}

bool	Dates::operator<(const Dates &rhs) const {
	return (year <= rhs.year && month <= rhs.month && day <= rhs.day);
}

BitcoinExchange::BitcoinExchange(std::string &filename) {
	_inputFile.open(filename);
	_database.open("data.csv");
	if (!_inputFile.is_open() || !_database.is_open())
		throw std::invalid_argument("Files not found.");
}

BitcoinExchange::~BitcoinExchange(void) {
	if (_inputFile.is_open())
		_inputFile.close();
	if (_database.is_open())
		_database.close();
	_input.clear();
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &copy): _input(copy._input) {
}

BitcoinExchange	&BitcoinExchange::operator=(const BitcoinExchange &rhs) {
	if (this != &rhs) {
		_input = rhs._input;
	}
	return (*this);
}

static Dates	getDates(std::string str, std::map<Dates, float> &map) {
	Dates	date;
	size_t	pos = str.find(" | ");

	date.errorCode = 0;
	if (str.empty() || str == "date | value")
		return (date);
	if (pos == str.npos) {
		date.errorCode = 1;
		map[date] = 0;
		return (date);
	}
	std::string	dateStr = str.substr(0, pos);
	str.erase(0, pos + 3);
	try {
		pos = dateStr.find('-');
		date.year = std::stoi(dateStr.substr(0, pos));
		date.month = std::stoi(dateStr.substr(pos + 1, 2));
		pos = dateStr.find('-', pos + 1);
		date.day = std::stoi(dateStr.substr(pos + 1, 2));
		float	val = std::stof(str.substr(0, 4));
		if (val < 0)
			date.errorCode = 2;
		else if (val > 1000)
			date.errorCode = 3;
		if (date.day <= 0 || date.day > 12 || date.month <= 0 || date.month > 12 || date.year <= 2008 || date.year > 2030)
			date.errorCode = 1;
		map[date] = val;
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
	return (date);
}

void	BitcoinExchange::initMap(void) {
	char	str[255];

	while (!_inputFile.fail()) {
		_inputFile.getline(str, 255, '\n');
		getDates(std::string(str), _input);
	}
}

static Dates	convertDate(std::string date) {
	Dates	cDate;

	try {
		cDate.year = std::stoi(date.substr(0, date.find('-')));
		date.erase(0, date.find('-') + 1);
		cDate.month = std::stoi(date.substr(0, date.find('-')));
		date.erase(0, date.find('-') + 1);
		cDate.day = std::stoi(date);
		cDate.errorCode = 0;
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
	return (cDate);
}

static int	getDifference(Dates date, Dates dateDb) {
	int	diff = 0;

	if (date.year > dateDb.year)
		diff += (date.year - dateDb.year) * 365;
	else
		diff += (dateDb.year - date.year) * 365;
	if (date.month > dateDb.month)
		diff += (date.month - dateDb.month) * 30;
	else
		diff += (dateDb.month - date.month) * 30;
	diff += (date.day - dateDb.day);
	return (diff);
}

float	BitcoinExchange::getPrice(std::map<Dates, float>::iterator &it) {
	float	price = 0.0;
	float	priced = 0.0;
	char	str[255];
	int	diff = 99999;

	_database.clear();
	_database.seekg(0);
	while (!_database.fail()) {
		_database.getline(str, 255, '\n');
		std::string	r = str;
		if (r == "date,exchange_rate")
			continue;
		if (r.empty())
			break;
		std::string	d = r.substr(0, ',');
		r.erase(0, r.find(',') + 1);
		Dates	date = convertDate(d);
		price = std::stof(r);
		if (date == (*it).first)
			return ((*it).second * price);
		else if (diff > getDifference(date, (*it).first)) {
			diff = getDifference(date, (*it).first);
			priced = price;
		}
	}
	return ((*it).second * priced);
}

void	BitcoinExchange::printIn(void) {
	for (std::map<Dates, float>::iterator it = _input.begin(); it != _input.end(); it++) {
		if ((*it).first.errorCode == 0)
			std::cout << (*it).first.year << "-" << (*it).first.month << "-" << (*it).first.day << " => " << (*it).second << " = " << getPrice(it) << std::endl;
		else if ((*it).first.errorCode == 1)
			std::cerr << "Error: bad input." << std::endl;
		else if ((*it).first.errorCode == 2)
			std::cerr << "Error: not a positive number." << std::endl;
		else if ((*it).first.errorCode == 3)
			std::cerr << "Error: too large number." << std::endl;
	}
}

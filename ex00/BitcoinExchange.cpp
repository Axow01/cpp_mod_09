/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:46:04 by mmarcott          #+#    #+#             */
/*   Updated: 2024/03/14 16:15:05 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

bool	Dates::operator==(const Dates &rhs) const {
	return (id == rhs.id);
}

bool	Dates::operator<(const Dates &rhs) const {
	return (id < rhs.id);
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

static bool	checkLeapYear(const Dates &date) {
	if (date.year % 4 == 0 || date.year % 400 == 0)
		return (true);
	return(false);
}

static bool	checkMonthDay(const Dates &date) {
	t_month	month;

	switch (date.month) {
	case 1: month = JAN; break;
	case 2: month = FEB; break;
	case 3: month = MAR; break;
	case 4: month = APR; break;
	case 5: month = MAY; break;
	case 6: month = JUN; break;
	case 7: month = JUL; break;
	case 8: month = AUG; break;
	case 9: month = SEP; break;
	case 10: month = OCT; break;
	case 11: month = NOV; break;
	case 12: month = DEC; break;
	default: month = NONE;
	}
	if (checkLeapYear(date))
		month = FEBL;
	std::cout << "Month: " << month << std::endl;
	if (month != NONE && date.day <= month && date.day > 0)
		return (true);
	return (false);
}

static Dates	getDates(std::string str, std::map<Dates, float> &map) {
	static int	id = -1;
	Dates	date;
	size_t	pos = str.find(" | ");

	date.errorCode = 0;
	date.id = ++id;
	if (str.empty() || str == "date | value")
		return (date);
	if (pos == str.npos) {
		date.errorCode = 1;
		map.insert(std::make_pair(date, 0));
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
		if (val < 0 || val == -0)
			date.errorCode = 2;
		else if (val > 1000)
			date.errorCode = 3;
		if (date.year <= 2008 || !checkMonthDay(date))
			date.errorCode = 1;
		map.insert(std::make_pair(date, val));
	} catch (std::exception &e) {
		std::cout << "Error: " << e.what() << std::endl;
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

	diff += (date.year - dateDb.year) * 365;
	diff += (date.month - dateDb.month) * 30;
	diff += (date.day - dateDb.day);
	if (diff < 0)
		std::cerr << "Error: diff is not positive!" << std::endl;
	return (diff);
}

static bool	isLower(Dates dateInput, Dates dateDb) {
	if (dateDb.year > dateInput.year)
		return (false);
	if ((dateDb.year == dateInput.year && dateDb.month > dateInput.month) || (dateDb.year == dateInput.year && dateDb.month == dateInput.month && dateDb.day >= dateInput.day))
		return (false);
	return (true);
}

static bool	isDateEqual(Dates d1, Dates d2) {
	if (d1.year == d2.year && d1.month == d2.month && d1.day == d2.day)
		return (true);
	return (false);
}

double	BitcoinExchange::getPrice(std::map<Dates, float>::iterator &it) {
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
		if (isDateEqual(date, (*it).first))
			return ((*it).second * price);
		else if (isLower((*it).first, date) && diff > getDifference((*it).first, date)) {
			diff = getDifference((*it).first, date);
			priced = price;
		}
	}
	std::cout.setf(std::ios::fixed, std::ios::floatfield);
	std::cout.precision(2);
	return ((*it).second * priced);
}

static std::string	formatDate(int date) {
	std::string	dateStr = "0";

	dateStr += std::to_string(date);
	if (dateStr.length() > 2)
		dateStr.erase(0, 1);
	return (dateStr);
}

void	BitcoinExchange::printIn(void) {
	for (std::map<Dates, float>::iterator it = _input.begin(); it != _input.end(); it++) {
		if ((*it).first.errorCode == 0)
			std::cout << (*it).first.year << "-" << formatDate((*it).first.month) << "-" << formatDate((*it).first.day) << " => " << (*it).second << " = " << getPrice(it) << std::endl;
		else if ((*it).first.errorCode == 1)
			std::cerr << "Error: bad input." << std::endl;
		else if ((*it).first.errorCode == 2)
			std::cerr << "Error: not a positive number." << std::endl;
		else if ((*it).first.errorCode == 3)
			std::cerr << "Error: too large number." << std::endl;
		std::cout.unsetf(std::ios::fixed);
		std::cout.unsetf(std::ios::floatfield);
		std::cout.precision(6);
	}
}

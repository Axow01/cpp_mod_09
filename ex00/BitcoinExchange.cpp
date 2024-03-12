/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:46:04 by mmarcott          #+#    #+#             */
/*   Updated: 2024/03/12 14:39:15 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <string>

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

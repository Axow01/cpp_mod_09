/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:46:04 by mmarcott          #+#    #+#             */
/*   Updated: 2024/03/11 18:18:50 by mmarcott         ###   ########.fr       */
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

BitcoinExchange::BitcoinExchange(const BitcoinExchange &copy): _input(copy._input) {
}

BitcoinExchange	&BitcoinExchange::operator=(const BitcoinExchange &rhs) {
	if (this != &rhs) {
		_input = rhs._input;
	}
	return (*this);
}

void	BitcoinExchange::initMap(void) {
	char	str[255];

	while (!_inputFile.fail()) {
		_inputFile.getline(str, 255, '\n');
	}
}

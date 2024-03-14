/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:46:14 by mmarcott          #+#    #+#             */
/*   Updated: 2024/03/14 16:12:25 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HPP_BITCOINEXCHANGE
# define HPP_BITCOINEXCHANGE

# include <iostream>
# include <fstream>
# include <map>
# include <stdexcept>
# include <string>

typedef enum	e_month {
	JAN = 31,
	FEB = 28,
	FEBL = 29,
	MAR = 31,
	APR = 30,
	MAY = 31,
	JUN = 30,
	JUL = 31,
	AUG = 31,
	SEP = 30,
	OCT = 31,
	NOV = 30,
	DEC = 31,
	NONE = -1
}		t_month;

struct Dates {
	int	id;
	int	year;
	int	month;
	int	day;
	int	errorCode; // 0 = all good, 1 = Bad input, 2 = Not positive number, 3 = too Large Number.
	bool	operator==(const Dates &rhs) const;
	bool	operator<(const Dates &rhs) const;
};

class BitcoinExchange {
	private:
		std::map<Dates, float>	_input;
		std::ifstream			_database;
		std::ifstream			_inputFile;
	public:
		BitcoinExchange(std::string &filename);
		BitcoinExchange(const BitcoinExchange &copy);
		~BitcoinExchange(void);

		BitcoinExchange	&operator=(const BitcoinExchange &rhs);

		void	initMap(void);
		double	getPrice(std::map<Dates, float>::iterator &it);
		void	printIn(void);
};

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:46:14 by mmarcott          #+#    #+#             */
/*   Updated: 2024/03/12 21:18:54 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HPP_BITCOINEXCHANGE
# define HPP_BITCOINEXCHANGE

# include <iostream>
# include <fstream>
# include <map>
# include <stdexcept>
# include <string>

struct Dates {
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
		float	getPrice(std::map<Dates, float>::iterator &it);
		void	printIn(void);
};

#endif

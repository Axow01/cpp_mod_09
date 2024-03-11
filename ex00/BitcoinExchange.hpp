/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:46:14 by mmarcott          #+#    #+#             */
/*   Updated: 2024/03/11 18:07:28 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HPP_BITCOINEXCHANGE
# define HPP_BITCOINEXCHANGE

# include <iostream>
# include <fstream>
# include <map>
# include <stdexcept>

struct Dates {
	int	year;
	int	month;
	int	day;
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
};

#endif

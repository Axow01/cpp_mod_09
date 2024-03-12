/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:43:36 by mmarcott          #+#    #+#             */
/*   Updated: 2024/03/12 13:31:42 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int	main(int argc, char **argv) {
	std::string	input_file;

	if (argc != 2) {
		std::cerr << "Error: No arguements or too much arguements!" << std::endl;
		return (1);
	}
	input_file = argv[1];
	BitcoinExchange	exchange(input_file);

	exchange.initMap();
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:09:05 by mmarcott          #+#    #+#             */
/*   Updated: 2024/03/15 17:49:37 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

static std::string	createStringFromArgs(char **argv, int ac) {
	std::string	str;

	for (int i = 1; i != ac; i++) {
		str += argv[i];
	}
	size_t	pos = str.find(' ');
	while (pos != str.npos) {
		str.erase(pos, 1);
		pos = str.find(' ');
	}
	return (str);
}

int	main(int argc, char **argv) {
	if (argc < 2) {
		std::cerr << "Error: Missing some arguments." << std::endl;
		return (1);
	}
	std::string	w;
	w = createStringFromArgs(argv, argc);
	try {
		RPN	rpn(w);
		std::cout << rpn.solve() << std::endl;
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}

	return (0);
}

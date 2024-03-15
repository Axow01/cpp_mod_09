/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:52:47 by mmarcott          #+#    #+#             */
/*   Updated: 2024/03/15 19:11:35 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int	main(int argc, char **argv) {
	if (argc < 2) {
		std::cerr << "Error: Invalid Arguments." << std::endl;
		return (1);
	}
	std::string	str = argv[1];
	PmergeMe	mergeMe(str);

	mergeMe.sortVector();
	return (0);
}

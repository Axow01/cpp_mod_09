/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:52:47 by mmarcott          #+#    #+#             */
/*   Updated: 2024/03/19 17:33:33 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

static bool	isSorted(const std::vector<int> &s) {
	for (std::vector<int>::const_iterator it = s.cbegin(); it != s.cend(); it++) {
		for (std::vector<int>::const_iterator its = it; its != s.cbegin(); its--) {
			if (*its > *it)
				return (false);
		}
	}
	return (true);
}

static bool	isSortedDeque(const std::deque<int> &s) {
	for (std::deque<int>::const_iterator it = s.cbegin(); it != s.cend(); it++) {
		for (std::deque<int>::const_iterator its = it; its != s.cbegin(); its--) {
			if (*its > *it)
				return (false);
		}
	}
	return (true);
}

// static void	printDeque(std::deque<int> s) {
// 	for (std::deque<int>::iterator it = s.begin(); it != s.end(); it++)
// 		std::cout << *it << " ";
// 	std::cout << std::endl;
// }

int	main(int argc, char **argv) {
	if (argc < 2) {
		std::cerr << "Error: Invalid Arguments." << std::endl;
		return (1);
	}
	std::string	str;
	for (int i = 1; i < argc; i++) {
		str += argv[i];
		if (i != argc - 1)
			str += " ";
	}
	PmergeMe	mergeMe(str);

	std::cout << "Before: ";
	mergeMe.sortVector();
	mergeMe.sortDeque();
	std::cout << "After : ";
	printVect(mergeMe.getVector());
	std::cout.setf(std::ios::fixed, std::ios::floatfield);
	std::cout.precision(5);
	std::cout << "Time to process a range of " << mergeMe.getVector().size() << " elements with std::vector<int> : " << mergeMe.getTimeSpentVector() << " ms" << std::endl;
	std::cout << "Time to process a range of " << mergeMe.getDeque().size() << " elements with std::deque<int>  : " << mergeMe.getTimeSpentDeque() << " ms" << std::endl;
	std::cout << "Is it sorted Vector: " << isSorted(mergeMe.getVector()) << std::endl;
	std::cout << "Is it sorted Deque: " << isSortedDeque(mergeMe.getDeque()) << std::endl;
	return (0);
}

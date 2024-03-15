/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:53:04 by mmarcott          #+#    #+#             */
/*   Updated: 2024/03/15 19:17:19 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe(std::string &rawSequence): _rawSequence(rawSequence) {}

PmergeMe::PmergeMe(const PmergeMe &copy): _rawSequence(copy._rawSequence), _timeStartedOperation(copy._timeStartedOperation), _vector(copy._vector), _deque(copy._deque) {}

PmergeMe::~PmergeMe(void) {}

PmergeMe	&PmergeMe::operator=(const PmergeMe &rhs) {
	if (this != &rhs) {
		_deque = rhs._deque;
		_vector = rhs._vector;
		_timeStartedOperation = rhs._timeStartedOperation;
		_rawSequence = rhs._rawSequence;
	}
	return(*this);
}

std::vector<int>	PmergeMe::getVector(void) const {
	return (_vector);
}

std::deque<int>	PmergeMe::getDeque(void) const {
	return (_deque);
}

std::time_t	PmergeMe::getStartedTime(void) const {
	return (_timeStartedOperation);
}

void	PmergeMe::sortVector(void) {
	_timeStartedOperation = std::time(NULL);
	parseRawSequenceVector();
}

void	PmergeMe::parseRawSequenceVector(void) {
	for (size_t i = 0; _rawSequence[i]; i++) {
		if (!isnumber(_rawSequence[i]) && _rawSequence[i] != ' ')
			throw std::invalid_argument("Invalid arguments.");
	}
	while (!_rawSequence.empty()) {
		_vector.push_back(std::stoi(_rawSequence.substr(0, _rawSequence.find(' '))));
		_rawSequence.erase(0, _rawSequence.find(' ') + 1);
		if (_rawSequence.find(' ') == _rawSequence.npos) {
			_vector.push_back(std::stoi(_rawSequence));
			_rawSequence.clear();
		}
	}
	for (std::vector<int>::iterator it = _vector.begin(); it != _vector.end(); it++)
		std::cout << *it << std::endl;
}

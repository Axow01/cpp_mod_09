/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:53:04 by mmarcott          #+#    #+#             */
/*   Updated: 2024/03/19 17:32:57 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe(std::string &rawSequence): _rawSequence(rawSequence), _rawSequenceDeque(rawSequence) {}

PmergeMe::PmergeMe(const PmergeMe &copy): _rawSequence(copy._rawSequence), _rawSequenceDeque(copy._rawSequenceDeque), _timeStartedOperation(copy._timeStartedOperation), _vector(copy._vector), _deque(copy._deque), _timeSpentVector(copy._timeSpentVector), _timeSpentDeque(copy._timeSpentDeque) {}

PmergeMe::~PmergeMe(void) {}

PmergeMe	&PmergeMe::operator=(const PmergeMe &rhs) {
	if (this != &rhs) {
		_deque = rhs._deque;
		_vector = rhs._vector;
		_timeStartedOperation = rhs._timeStartedOperation;
		_rawSequence = rhs._rawSequence;
		_rawSequenceDeque = rhs._rawSequenceDeque;
		_timeSpentDeque = rhs._timeSpentDeque;
		_timeSpentVector = rhs._timeSpentVector;
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

int	PmergeMe::insertionSort(std::vector<int> &s, int nb, int L, int R) {
	int	M = (L + R) / 2;

	if (s.size() == 0) {
		return (0);
	}
	if (L > R)
		return (M);
	if (s[M] < nb)
		return (insertionSort(s, nb, M + 1, R));
	if (s[M] > nb)
		return (insertionSort(s, nb, L, M - 1));
	if (s[M] == nb)
		return (M);
	return (M);
}

void	printVect(std::vector<int> s) {
	for (std::vector<int>::iterator it = s.begin(); it != s.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
}

static void	addToV(int idx, std::vector<int> &s, int nb) {
	std::vector<int>::iterator	it = s.begin() + idx;

	if (it != s.end() && *it < nb)
		it++;
	s.insert(it, nb);
}

std::vector<int>	&PmergeMe::completeSort(std::vector<int> &s) {
	while (!_vector.empty()) {
		int nb = _vector.front();
		addToV(insertionSort(s, nb, 0, s.size() - 1), s, nb);
		_vector.erase(_vector.begin());
	}
	return (s);
}

void	PmergeMe::sortVector(void) {
	int					n;
	size_t				i = 0;
	std::vector<int>	s;

	_timeStartedOperation = std::clock();
	parseRawSequenceVector();
	printVect(_vector);
	n = _vector.size() / 2;
	for (int i_groups = 0; i_groups < n; i_groups++) {
		int	p = 0;
		if (i > _vector.size() - 1)
			break;
		if (_vector[i] > _vector[i + 1]) {
			p = insertionSort(s, _vector[i], 0, s.size() - 1);
			addToV(p, s, _vector[i]);
		} else {
			p = insertionSort(s, _vector[i + 1], 0, s.size() - 1);
			addToV(p, s, _vector[i + 1]);
		}
		i += 2;
	}
	for (size_t i_g = 0; i_g < _vector.size(); i_g++) {
		static size_t	found = 0;
	
		if (found >= s.size())
			break;
		for (std::vector<int>::iterator it = s.begin(); it != s.end(); it++) {
			if (*it == _vector[i_g]) {
				found++;
				_vector.erase(_vector.begin() + i_g);
				i_g--;
				break;
			}
		}
	}
	completeSort(s);
	_vector = s;
	s.clear();
	_timeSpentVector = getTimedUsed();
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
}

double	PmergeMe::getTimedUsed(void) {
	std::clock_t	endTime = std::clock();

	double duration = ((double)(endTime - _timeStartedOperation) / (double)CLOCKS_PER_SEC) * 1000.0;
	return (duration);
}

double	PmergeMe::getTimeSpentVector(void) const {
	return (_timeSpentVector);
}

double	PmergeMe::getTimeSpentDeque(void) const {
	return (_timeSpentDeque);
}

int	PmergeMe::insertionSortDeque(std::deque<int> &s, int nb, int L, int R) {
	int	M = (L + R) / 2;

	if (L > R)
		return (M);
	if (s[M] < nb)
		return (insertionSortDeque(s, nb, M + 1, R));
	if (s[M] > nb)
		return (insertionSortDeque(s, nb, L, M - 1));
	if (s[M] == nb)
		return (M);
	return (M);
}

static void	addDequeS(int idx, std::deque<int> &s, int nb, std::deque<int> &d) {
	std::deque<int>::iterator	it = s.begin() + idx;

	if (it != s.end() && *it < nb)
		it++;
	s.insert(it, nb);
	for (std::deque<int>::iterator its = d.begin(); its != d.end(); its++) {
		if (*its == nb) {
			d.erase(its);
			break;
		}
	}
}

void	PmergeMe::parseRawSequenceDeque(void) {
	for (size_t i = 0; _rawSequenceDeque[i]; i++) {
		if (!isnumber(_rawSequenceDeque[i]) && _rawSequenceDeque[i] != ' ')
			throw std::invalid_argument("Invalid arguments.");
	}
	while (!_rawSequenceDeque.empty()) {
		_deque.push_back(std::stoi(_rawSequenceDeque.substr(0, _rawSequenceDeque.find(' '))));
		_rawSequenceDeque.erase(0, _rawSequenceDeque.find(' ') + 1);
		if (_rawSequenceDeque.find(' ') == _rawSequenceDeque.npos) {
			_deque.push_back(std::stoi(_rawSequenceDeque));
			_rawSequenceDeque.clear();
		}
	}
}

void	PmergeMe::sortDeque(void) {
	size_t		i = 0;
	std::deque<int>	s;

	_timeStartedOperation = std::clock();
	parseRawSequenceDeque();
	for (size_t iGroup = 0; iGroup < _deque.size() / 2; iGroup++) {
		if (i > _deque.size() - 1)
			break;
		if (_deque[i] > _deque[i + 1]) {
			addDequeS(insertionSortDeque(s, _deque[i], 0, s.size() - 1), s, _deque[i], _deque);
			i--;
		}
		else {
			addDequeS(insertionSortDeque(s, _deque[i + 1], 0, s.size() - 1), s, _deque[i + 1], _deque);
			i--;
		}
		i += 2;
	}
	while (!_deque.empty()) {
		addDequeS(insertionSortDeque(s, _deque.front(), 0, s.size() - 1), s, _deque.front(), _deque);
	}
	_deque = s;
	_timeSpentDeque = ((double)(std::clock() - _timeStartedOperation) / (double)CLOCKS_PER_SEC) * 1000.0;
}

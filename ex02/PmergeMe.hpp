/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:53:13 by mmarcott          #+#    #+#             */
/*   Updated: 2024/03/19 17:17:26 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HPP_PMERGEME
# define HPP_PMERGEME

# include <iostream>
# include <algorithm>
# include <vector>
# include <deque>
# include <ctime>

class PmergeMe {
	public:
		PmergeMe(std::string &rawSequence);
		PmergeMe(const PmergeMe &copy);
		~PmergeMe(void);

		PmergeMe	&operator=(const PmergeMe &rhs);

		std::vector<int>	getVector(void) const;
		std::deque<int>		getDeque(void) const;
		std::time_t			getStartedTime(void) const;
		void				sortVector(void);
		void				sortDeque(void);
		double				getTimedUsed(void);
		double				getTimeSpentVector(void) const;
		double				getTimeSpentDeque(void) const;
	private:
		int					insertionSort(std::vector<int> &s, int nb, int L, int R);
		int					insertionSortDeque(std::deque<int> &s, int nb, int L, int R);
		void				parseRawSequenceVector(void);
		void				parseRawSequenceDeque(void);
		std::vector<int>	&completeSort(std::vector<int> &s);
		std::string			_rawSequence;
		std::string			_rawSequenceDeque;
		std::clock_t		_timeStartedOperation;
		std::vector<int>	_vector;
		std::deque<int>		_deque;
		double				_timeSpentVector;
		double				_timeSpentDeque;
};

void	printVect(std::vector<int> s);

#endif

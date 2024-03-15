/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:53:13 by mmarcott          #+#    #+#             */
/*   Updated: 2024/03/15 18:55:55 by mmarcott         ###   ########.fr       */
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
	private:
		void				parseRawSequenceVector(void);
		std::string			_rawSequence;
		std::time_t			_timeStartedOperation;
		std::vector<int>	_vector;
		std::deque<int>		_deque;
};

#endif

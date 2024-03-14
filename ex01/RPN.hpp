/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:09:32 by mmarcott          #+#    #+#             */
/*   Updated: 2024/03/14 16:33:17 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HPP_RPN
# define HPP_RPN

# include <iostream>
# include <string>
# include <stack>

typedef enum e_operator {
	ADD,
	MINUS,
	DIVIDE,
	MULTIPLY
}		t_operator;

class RPN {
	public:
		RPN(std::string &rawRPN);
		RPN(const RPN &copy);
		~RPN(void);

		RPN	&operator=(const RPN &rhs);

		int	solve(void);
	private:
		std::stack<int>	_rpn;
		std::string		_rawRPN;
};

#endif

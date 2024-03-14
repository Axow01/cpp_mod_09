/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:09:34 by mmarcott          #+#    #+#             */
/*   Updated: 2024/03/14 16:57:54 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN(std::string &rawRPN): _rawRPN(rawRPN) {
	if (rawRPN.empty())
		throw std::invalid_argument("Empty expression.");
}

RPN::RPN(const RPN &copy): _rpn(copy._rpn), _rawRPN(copy._rawRPN) {}

RPN::~RPN(void) {}

RPN	&RPN::operator=(const RPN &rhs) {
	if (this != &rhs) {
		_rpn = rhs._rpn;
		_rawRPN = rhs._rawRPN;
	}
	return (*this);
}

static void	compute(std::stack<int> &rpn, t_operator op) {
	int	operand[2];

	operand[1] = rpn.top();
	rpn.pop();
	operand[0] = rpn.top();
	rpn.pop();
	switch (op) {
	case ADD: rpn.push(operand[0] + operand[1]); break;
	case MINUS: rpn.push(operand[0] - operand[1]); break;
	case DIVIDE: rpn.push(operand[0] / operand[1]); break;
	case MULTIPLY: rpn.push(operand[0] * operand[1]); break;
	}
}

int	RPN::solve(void) {
	t_operator	op;
	for (size_t i = 0; _rawRPN[i]; i++) {
		if (isdigit(_rawRPN[i])) {
			_rpn.push((int)(_rawRPN[i] - '0'));
			continue;
		}
		switch (_rawRPN[i]) {
		case '+': op = ADD; break;
		case '-': op = MINUS; break;
		case '/': op = DIVIDE; break;
		case '*': op = MULTIPLY; break;
		default: throw std::invalid_argument("Wrong expressions."); break;
		}
		compute(_rpn, op);
	}
	std::cout << "Size: " << _rpn.size() << std::endl;
	return (_rpn.top());
}

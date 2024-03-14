/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:09:34 by mmarcott          #+#    #+#             */
/*   Updated: 2024/03/13 20:31:49 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN(std::string &rawRPN): _operandCount(0), _operatorCount(0) {
	if (rawRPN.empty())
		throw std::invalid_argument("Empty expression.");
	for (size_t i = 0; rawRPN[i]; i++) {
		if (isdigit(rawRPN[i])) {
			_operandCount++;
			_rpn.push((int)(rawRPN[i] - '0'));
		}
		switch (rawRPN[i]) {
		case '+':
			_operandCount++;
			_rpn.push(ADD);
			break;
		case '-':
			_operandCount++;
			_rpn.push(MINUS);
			break;
		case '/':
			_operandCount++;
			_rpn.push(DIVIDE);
			break;
		case '*':
			_operandCount++;
			_rpn.push(MULTIPLY);
			break;
		case 'S':
			_rpn.push(-1);
		}
	}
	std::cout << "Top: " << _rpn.top() << std::endl;
}

RPN::RPN(const RPN &copy): _rpn(copy._rpn), _operandCount(copy._operandCount), _operatorCount(copy._operatorCount) {}

RPN::~RPN(void) {}

RPN	&RPN::operator=(const RPN &rhs) {
	if (this != &rhs) {
		_rpn = rhs._rpn;
		_operandCount = rhs._operandCount;
		_operatorCount = rhs._operatorCount;
	}
	return (*this);
}

int	RPN::solve(void) const {
	while (!_rpn.empty()) {
		
	}
	return (0);
}

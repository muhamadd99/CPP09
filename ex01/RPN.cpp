/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbani-ya <mbani-ya@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 18:15:12 by mbani-ya          #+#    #+#             */
/*   Updated: 2026/03/10 00:10:18 by mbani-ya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <iostream>

RPN::RPN(std::string str) : _str(str)
{}

RPN::RPN(const RPN& other) : _str(other._str)
{}

RPN& RPN::operator=(const RPN& other)
{
	if (this != &other)
		_str = other._str;
	return *this;
}

RPN::~RPN()
{}

void	RPN::runInput()
{
	for (size_t i = 0; i < _str.length(); i++)
	{
		if (_str[i] == ' ')
		{
			continue ;
		}
		else if (std::isdigit(_str[i]))
		{
			_nbr.push(_str[i] - '0');
		}
		else if (checkOperator(_str[i]))
		{
			if (handleOperator(i))
				return ;
		}
		else
		{
			std::cerr << "Error: Wrong characters" << std::endl;
			return ;
		}
	}
	if (_nbr.size() != 1)
		std::cerr << "Error: Unfinished number" << std::endl;
	else
		std::cout << _nbr.top() << std::endl;
}

int RPN::handleOperator(int i)
{
	if (_nbr.size() < 2)
	{
		std::cerr << "Error: not enough number" << std::endl;
		return 1;
	}
	int b = _nbr.top();
	_nbr.pop();
	int a = _nbr.top();
	_nbr.pop();
	if (_str[i] == '/')
	{
		if (b == 0)
		{
			std::cerr << "Error: division by 0" << std::endl;
			return 1;
		}
		_nbr.push(a / b);
	}
	else if (_str[i] == '*')
		_nbr.push(a * b);
	else if (_str[i] == '-')
		_nbr.push(a - b);
	else if (_str[i] == '+')
		_nbr.push(a + b);
	return (0);
}

int	RPN::checkOperator(char c)
{
	if (c == '*')
		return 1;
	if (c == '/')
		return 1;
	if (c == '+')
		return 1;
	if (c == '-')
		return 1;
	return 0;
}

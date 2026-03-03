/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbani-ya <mbani-ya@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 18:15:06 by mbani-ya          #+#    #+#             */
/*   Updated: 2026/03/02 11:36:02 by mbani-ya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <stack>

class RPN {
private:
	std::stack<int> _nbr;
	std::string	_str;
public:
	RPN(std::string str);
	RPN(const RPN& other);
	RPN& operator=(const RPN& other);
	~RPN();
	void	runInput();
	int		checkOperator(char c);
	int		handleOperator(int i);
};
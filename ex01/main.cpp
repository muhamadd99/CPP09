/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbani-ya <mbani-ya@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 18:15:25 by mbani-ya          #+#    #+#             */
/*   Updated: 2026/03/02 11:37:12 by mbani-ya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <iostream>

int main (int ac, char **av)
{
	if (ac != 2)
	{
		std::cout << "not 2 argument" << std::endl;
		return 1;
	}
	RPN calculate(av[1]);
	calculate.runInput();
	return 0;
}

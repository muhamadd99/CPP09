/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbani-ya <mbani-ya@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 15:32:00 by mbani-ya          #+#    #+#             */
/*   Updated: 2026/03/08 22:50:03 by mbani-ya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <iostream>
#include "BitcoinExchange.hpp"

int main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cout << "Need one input file" << std::endl;
		return 1;
	}
	std::string file = av[1];
	BitcoinExchange	exchange(file);
	exchange.parseRate();
	exchange.processInput();
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbani-ya <mbani-ya@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 17:51:30 by mbani-ya          #+#    #+#             */
/*   Updated: 2026/03/03 11:11:25 by mbani-ya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>
#include "PmergeMe.hpp"

static int	strdigit(const char* str);

int main(int ac, char **av)
{
	std::vector<int> input;

	if (ac == 1)
	{
		std::cerr << "No input" << std::endl;
		return 1;
	}
	else if (ac == 2)
	{
		std::stringstream ss(av[1]); //can i give char* str directly?
		std::string tmp;

		while (ss >> tmp)
		{
			if (!strdigit(tmp.c_str()))
			{
				std::cerr << "Error: Wrong input" << std::endl;
				return 1;
			}
			input.push_back(atoi(tmp.c_str()));
		}
		if (input.size() == 1)
		{
			std::cerr << "Error: Wrong input" << std::endl;
			return 1;
		}
	}
	else
	{
		for (int i = 1; av[i]; i++)
		{
			if (!strdigit(av[i]))
			{
				std::cerr << "Error: Wrong input" << std::endl;
				return 1;
			}
			else
				input.push_back(atoi(av[i]));
		}
	}

	PmergeMe	object(input);
	object.printVector(input);
	object.process();

	return 0;
}

int	strdigit(const char* str)
{
	for (int i = 0; str[i]; i++)
	{
		if (!std::isdigit(str[i]))
			if (!(i == 0 && str[i] == '+' && std::isdigit(str[i + 1])))
				return 0;
	}
	return 1;
}

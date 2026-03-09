/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbani-ya <mbani-ya@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 17:51:30 by mbani-ya          #+#    #+#             */
/*   Updated: 2026/03/09 12:59:50 by mbani-ya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <cstdlib>
#include "PmergeMe.hpp"

int main(int ac, char **av)
{
	std::vector<int> input;
	
	PmergeMe	pmergeme;

	pmergeme.runPrint(ac, av);
}

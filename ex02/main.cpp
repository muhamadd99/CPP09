/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbani-ya <mbani-ya@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 17:51:30 by mbani-ya          #+#    #+#             */
/*   Updated: 2026/03/09 11:02:09 by mbani-ya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include <cstdlib>
#include "PmergeMe.hpp"

int main(int ac, char **av)
{
	std::vector<int> input;
	
	PmergeMe	pmergeme;

	pmergeme.runPrint(ac, av);
}

// PmergeMe	vec;
// vec.runVector(ac, av);
// vec.processVec();
// PmergeMe	deq;
// deq.runDeque(ac, av);
// //deq.processDeq();
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbani-ya <mbani-ya@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 18:51:45 by mbani-ya          #+#    #+#             */
/*   Updated: 2026/03/03 10:47:39 by mbani-ya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <iostream>

PmergeMe::PmergeMe(std::vector<int>& nbr) :_nbr(nbr)
{}

PmergeMe::PmergeMe(const PmergeMe& other) : _nbr(other._nbr)
{}

PmergeMe& PmergeMe::operator=(const PmergeMe& other) 
{
	if (this != &other)
		_nbr = other._nbr;
	return *this;
}

PmergeMe::~PmergeMe()
{}

void PmergeMe::printVector(const std::vector<int>& vec)
{
	for (size_t i = 0; i < vec.size(); ++i)
	{
		std::cout << vec[i];
		if (i < vec.size() - 1)
            std::cout << " ";
    }
    std::cout << std::endl;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbani-ya <mbani-ya@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 18:51:45 by mbani-ya          #+#    #+#             */
/*   Updated: 2026/03/03 13:41:11 by mbani-ya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <iostream>
#include <utility> //pair

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

void PmergeMe::process()
{
	// std::vector<std::pair<int, int> >	pairs;

	// for (int i = 0; i < _nbr.size(); i += 2)
	// {
	// 	if (i + 1 >= _nbr.size())
	// 	{
	// 		//odd number handling
	// 		continue ; //to skip even number handling
	// 	}
	// 	int	a;
	// 	int	b;
	// 	if (_nbr[i] > _nbr[i + 1])
	// 	{
	// 		a = _nbr[i];
	// 		b = _nbr[i + 1];
	// 	}
	// 	else
	// 	{
	// 		a = _nbr[i + 1];
	// 		b = _nbr[i];
	// 	}
	// 	pairs.push_back(std::make_pair(a, b));
	// }
	recurse(_nbr);
}

void PmergeMe::recurse(std::vector<int> tmp)
{
	std::vector<std::pair<int, int> >	pairs;
	int	oddNbr = 0;

	if (tmp.size() <= 1)
		return ; 

	for (int i = 0; i < tmp.size(); i += 2)
	{
		if (i + 1 >= tmp.size())
		{
			//odd number handling. where to store the number? in pending
			oddNbr = tmp[i];
			continue ; //to skip even number handling
		}
		else if (i + 1 < tmp.size())
		{
			int	a;
			int	b;
			if (tmp[i] > tmp[i + 1])
			{
				a = _nbr[i];
				b = _nbr[i + 1];
			}
			else
			{
				a = tmp[i + 1];
				b = tmp[i];
			}
			pairs.push_back(std::make_pair(a, b));
		}
	}
	//create main
	std::vector<int> main;
	
	for(int i = 0; i < pairs.size(); i++)
		main.push_back(pairs[i].first); 
		
	recurse(main);
	
	//create pending based on main
	std::vector<int> pending;	
	
	for(int i = 0; i < main.size(); i++)
		for (int j = 0; j < pairs.size(); j++)
			if (main[i] == pairs[j].first)
				pending.push_back(pairs[j].second);
	if (oddNbr)
		pending.push_back(oddNbr);

	//push pending to main
	//1st
	main.push_back(pending[0]);
	//3rd,5th,11th. so we must check pending.size() is divisible by jacobsthal or not. am i correct?
	//lets say nbr is 9. our jacobsthal will find 5 produces 0. so how do we solve the remaining?
	//the remaining is size() > 5. so i have to push element size()(8th). then element size() - 1(7th). then element size() - 2(6th) until it reaches the jacobsthall.
	//then repeat according to next jacobsthal until next jacobsthal. is it like that?
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbani-ya <mbani-ya@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 18:51:45 by mbani-ya          #+#    #+#             */
/*   Updated: 2026/03/04 17:42:04 by mbani-ya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <iostream>
#include <utility> //pair
#include <algorithm>

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
	makeJacobSeq();
	recurse(_nbr);
}

//the limit is 10923
void PmergeMe::makeJacobSeq()
{
	_jacobSeq.clear();
	_jacobSeq.push_back(3);
	_jacobSeq.push_back(5);
	
	int nbr = 0;
	while (_jacobSeq.back() < 10923)
	{
		nbr = _jacobSeq.back() + (2 * _jacobSeq[_jacobSeq.size() - 2]);
		_jacobSeq.push_back(nbr);
	}
	return ;
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
				a = tmp[i];
				b = tmp[i + 1];
			}
			else //so equal would take 2nd and put in main, then 1st in pending
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
	main.insert(main.begin(), pending[0]);

	int	lastInsertedIndex = 1;
	for (int i = 0; i < _jacobSeq.size(); i++)
	{
		int currJacobNbr = _jacobSeq[i];
		
		int currLimit = std::min<int>(currJacobNbr, pending.size());
		for (int j = currLimit; j > lastInsertedIndex; j--)
		{
			int value = pending[j - 1];

			auto insertLoc = std::lower_bound(main.begin(), main.end(), value);
			main.insert(insertLoc, value);
		}
		lastInsertedIndex = currLimit;
		
		if (lastInsertedIndex == currLimit)
			break ;
	}
}


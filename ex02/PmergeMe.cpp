/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbani-ya <mbani-ya@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 18:51:45 by mbani-ya          #+#    #+#             */
/*   Updated: 2026/03/07 13:59:27 by mbani-ya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <iostream>
#include <iterator>
#include <utility> //pair
#include <algorithm>
#include <sstream>

PmergeMe::PmergeMe() : _comparison(0)
{}

PmergeMe::PmergeMe(const PmergeMe& other) : _nbr(other._nbr), _comparison(0)
{}

PmergeMe& PmergeMe::operator=(const PmergeMe& other) 
{
	if (this != &other)
	{
		_nbr = other._nbr;
		_comparison = other._comparison;
	}
	return *this;
}

PmergeMe::~PmergeMe()
{}

void PmergeMe::runVector(int ac,  char **av)
{
	if (ac == 1)
		return printErr("No Input");
	else if (ac == 2)
	{
		std::stringstream ss(av[1]); //can i give char* str directly?
		std::string tmp;

		while (ss >> tmp)
		{
			if (!strdigit(tmp.c_str()))
				return printErr("Wrong Input");
			_nbr.push_back(atoi(tmp.c_str()));
		}
		if (_nbr.size() == 1)
			std::cout << _nbr[0] << std::endl;
	}
	else
	{
		for (int i = 1; av[i]; i++)
		{
			if (!strdigit(av[i]))
				return printErr("Wrong Input");
			else
				_nbr.push_back(atoi(av[i]));
		}
	}
}

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

void PmergeMe::processVec()
{
	makeJacobSeq();
	std::vector<Chain> number;
	std::vector<Chain> sorted;
	for (size_t i = 0; i < _nbr.size(); i++)
	{
		Chain c;
		c.winner = _nbr[i];
		number.push_back(c);
	}
	sorted = recurse(number);
	for (size_t i = 0; i < sorted.size(); i++)
		_sortedVec.push_back(sorted[i].winner);
	std::cout << "Before: ";
	printVector(_nbr);
	std::cout << std::endl;
	std::cout << "After: ";
	printVector(_sortedVec);
	std::cout << std::endl;
	std::cout << "No of comparisons: " << _comparison << std::endl;
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

int	PmergeMe::strdigit(const char* str)
{
	for (int i = 0; str[i]; i++)
	{
		if (!std::isdigit(str[i]))
			if (!(i == 0 && str[i] == '+' && std::isdigit(str[i + 1])))
				return 0;
	}
	return 1;
}

void	PmergeMe::printErr(std::string str)
{
	std::cerr << "Error: " << str << std::endl;
}


std::vector<Chain>	PmergeMe::recurse(std::vector<Chain> tmp)
{
	//			SEPARATE PENDING AND MAIN
	if (tmp.size() <= 1)
		return tmp;

	std::vector<Chain>	newLvl;
	bool				hasOdd = (tmp.size() % 2 != 0);
	Chain				oddChain;

	if (hasOdd)
	{
		oddChain = tmp.back();
		tmp.pop_back();
	}

	for (size_t i = 0; i < tmp.size(); i += 2)
	{
		_comparison++;
		if (tmp[i].winner > tmp[i + 1].winner)
		{
			tmp[i].losers.push_back(tmp[i + 1]);
			newLvl.push_back(tmp[i]);
		}
		else
		{
			tmp[i + 1].losers.push_back(tmp[i]);
			newLvl.push_back(tmp[i + 1]);
		}
	}
	//			RECURSION
	newLvl = recurse(newLvl);

	//			PRE JACOBSTHAL
	std::vector<Chain>	main;
	std::vector<Chain>	pending;

	for (size_t i = 0; i < newLvl.size(); i++)
	{
		pending.push_back(newLvl[i].losers.back());
		pending[i].pos = i; //added
		newLvl[i].losers.pop_back();
		main.push_back(newLvl[i]);
	}

	if (hasOdd)
	{
		oddChain.pos = main.size();
		pending.push_back(oddChain);
	}

	if (!pending.empty())
	{
		main.insert(main.begin(), pending[0]);
		for (size_t k = 0; k < pending.size(); k++)
			pending[k].pos++;
	}

	//			JACOBSTHAL
	size_t		lastInsertedPos = 1;
	Comparator	comp(_comparison);

	for (size_t i = 0; i < _jacobSeq.size(); i++)
	{
		size_t	jacobNo = _jacobSeq[i];
		size_t	currLimit = std::min<size_t>(jacobNo, pending.size());

		for (size_t j = currLimit; j > lastInsertedPos; j--)
		{
			Chain							val = pending[j - 1];
			std::vector<Chain>::iterator	insertLoc;

			// insertLoc = std::lower_bound(main.begin(), main.end(), val.winner, comp);
			std::vector<Chain>::iterator limit = main.begin() + pending[j - 1].pos; //added
			insertLoc = std::lower_bound(main.begin(), limit, val.winner, comp);
			size_t insertIdx = std::distance( main.begin(), insertLoc);//added
			main.insert(insertLoc, val);
			for(size_t k = 0; k < pending.size(); k++) //added
				if (pending[k].pos >= insertIdx) //added
					pending[k].pos++; //added
		}
		lastInsertedPos = currLimit;

		if (lastInsertedPos == pending.size())
			break;
	}

	return main;
}

bool	PmergeMe::chainCompare(const Chain& other, int value)
{
	return other.winner < value;
}

//not tested
void PmergeMe::runDeque(int ac, char **av)
{
	if (ac == 1)
		return printErr("No Input");
	else if (ac == 2)
	{
		std::stringstream ss(av[1]); //can i give char* str directly?
		std::string tmp;

		while (ss >> tmp)
		{
			if (!strdigit(tmp.c_str()))
				return printErr("Wrong Input");
			_nbrDeque.push_back(atoi(tmp.c_str()));
		}
		if (_nbr.size() == 1)
			std::cout << _nbr[0] << std::endl;
	}
	else
	{
		for (int i = 1; av[i]; i++)
		{
			if (!strdigit(av[i]))
				return printErr("Wrong Input");
			else
				_nbrDeque.push_back(atoi(av[i]));
		}
	}	
}

void PmergeMe::printDeque(const std::deque<int>& deq)
{
	for(size_t i = 0; i < deq.size(); ++i)
	{
		std::cout << deq[i];
		std::cout << " ";
	}
	std::cout << std::endl;
}

//not finished yet
void PmergeMe::processDeque()
{
	makeJacobSeq();
	std::vector<Chain> number;
	std::vector<Chain> sorted;
	for (size_t i = 0; i < _nbr.size(); i++)
	{
		Chain c;
		c.winner = _nbr[i];
		number.push_back(c);
	}
	sorted = recurse(number);
	for (size_t i = 0; i < sorted.size(); i++)
		_sortedVec.push_back(sorted[i].winner);
	std::cout << "Before: ";
	printVector(_nbr);
	std::cout << std::endl;
	std::cout << "After: ";
	printVector(_sortedVec);
	std::cout << std::endl;
	std::cout << "No of comparisons: " << _comparison << std::endl;
}

// std::vector<int> PmergeMe::recurse(std::vector<int> tmp)
// {
// 	//				FORD JOHNSON MAIN AND PENDING RECURSION
// 	std::vector<std::pair<int, int> >	pairs;
// 	int	oddNbr = -1;

// 	if (tmp.size() <= 1)
// 		return tmp; 

// 	for (int i = 0; i < tmp.size(); i += 2)
// 	{
// 		if (i + 1 >= tmp.size())
// 		{
// 			//odd number handling. where to store the number? in pending
// 			oddNbr = tmp[i];
// 			continue ; //to skip even number handling
// 		}
// 		else if (i + 1 < tmp.size())
// 		{
// 			int	a;
// 			int	b;
// 			if (tmp[i] > tmp[i + 1])
// 			{
// 				a = tmp[i];
// 				b = tmp[i + 1];
// 			}
// 			else //so equal would take 2nd and put in main, then 1st in pending
// 			{
// 				a = tmp[i + 1];
// 				b = tmp[i];
// 			}
// 			pairs.push_back(std::make_pair(a, b));
// 		}
// 	}
	
// 	//					PRE JACOBSTHAL
// 	//create main
// 	std::vector<int> main;
	
// 	for(int i = 0; i < pairs.size(); i++)
// 		main.push_back(pairs[i].first); 
		
// 	main = recurse(main);
	
// 	//create pending based on main
// 	std::vector<int> pending;
// 	std::vector<int> pairUsed(pairs.size(), false);
	
// 	for(int i = 0; i < main.size(); i++)
// 	{
// 		for (int j = 0; j < pairs.size(); j++)
// 		{
// 			if (main[i] == pairs[j].first && !pairUsed[j])
// 			{
// 				pairUsed[j] = true;
// 				pending.push_back(pairs[j].second);
// 				break ; 
// 			}
// 		}
// 	}
// 	if (oddNbr != -1) //bcus if use 1 it will be wrongly detect 0
// 		pending.push_back(oddNbr);

// 	//				JACOBSTHAL INSERTION
// 	//push pending to main
// 	//1st
// 	if (!pending.empty())
// 		main.insert(main.begin(), pending[0]);

// 	int lastInsertedPos = 1;
// 	for (int i = 0; i < _jacobSeq.size(); i++)
// 	{
// 		int jacobNo = _jacobSeq[i];
// 		int currLimit = std::min<int>(jacobNo, pending.size());

// 		for (int j = currLimit; j > lastInsertedPos; j--)
// 		{
// 			int value = pending[j - 1];
// 			auto insertLoc = std::lower_bound(main.begin(), main.end(), value);
// 			main.insert(insertLoc, value);
// 		}
// 		lastInsertedPos = currLimit;

// 		if (lastInsertedPos == pending.size())
// 			break ;
// 	}
// 	return (main);
// }



// std::vector<Chain> PmergeMe::recurse(std::vector<Chain> tmp)
// {
// 	//				FORD JOHNSON MAIN AND PENDING RECURSION
// 	std::vector<Chain>	newLvl;
// 	bool	hasOdd = false;
// 	Chain oddChain;
	
// 	if (tmp.size() <= 1)
// 		return tmp; 

// 	std::cout << "1" << std::endl; //debug
// 	for (size_t i = 0; i < tmp.size(); i += 2)
// 	{
// 		if (i + 1 >= tmp.size())// can be outside the loop after loop
// 		{
// 			hasOdd = true;
// 			oddChain = tmp.back();
// 		}
// 		else if (i + 1 < tmp.size())
// 		{
// 			_comparison++;
// 			if (tmp[i].winner > tmp[i + 1].winner)
// 			{
// 				tmp[i].losers.push_back(tmp[i + 1]); //change
// 				newLvl.push_back(tmp[i]);
// 			}
// 			else //so equal would take 2nd and put in main, then 1st in pending
// 			{
// 				tmp[i + 1].losers.push_back(tmp[i]); //change
// 				newLvl.push_back(tmp[i + 1]);
// 			}
// 		}
// 	}
// 	std::cout << "2" << std::endl; //debug
// 	//				RECURSION
// 	newLvl = recurse(newLvl);
	
// 	//create pending based on main
// 	std::vector<Chain> main;
// 	std::vector<Chain> pending;
	
// 	std::cout << "newLvl size:" << newLvl.size() << std::endl; //debug
// 	std::cout << "3" << std::endl; //debug
// 	std::cout << "newlvl size:  " << newLvl.size() << std::endl; //debug
// 	for(size_t i = 0; i < newLvl.size(); i++)
// 	{
// 		pending.push_back(newLvl[i].losers.back());
// 		std::cout << "losers back:  " << newLvl[i].losers.back().winner << "losers size: " << newLvl[i].losers.size() << std::endl;  //debug
// 		std::cout << "3a" << std::endl; //debug
// 		newLvl[i].losers.pop_back();
// 		//std::cout << "losers back2:  " << newLvl[i].losers.back().winner << "losers size2: " << newLvl[i].losers.size() << std::endl;  //debug
// 		std::cout << "3b" << std::endl; //debug
// 		std::cout << "newlvl size:  " << newLvl.size() << std::endl; //debug
// 		std::cout << "main size:  " << main.size() << std::endl; //debug
// 		std::cout << "i:  " << i << std::endl; //debug
// 		main.push_back(newLvl[i]);
// 		std::cout << "3c" << std::endl; //debug
// 	}
// 	std::cout << "3d" << std::endl; //debug
// 	if (hasOdd) //bcus if use 1 it will be wrongly detect 0
// 		pending.push_back(oddChain);

// 	std::cout << "4" << std::endl; //debug
// 	//				JACOBSTHAL INSERTION
// 	//push pending to main
// 	//1st
// 	if (!pending.empty())
// 	{
// 		std::cout << "4a" << std::endl; //debug
// 		Chain first;
// 		first = pending[0];
// 		main.insert(main.begin(), first);
// 	}
// 	size_t lastInsertedPos = 1;
// 	Comparator comp(_comparison);
// 	std::cout << "5" << std::endl; //debug
// 	for (size_t i = 0; i < _jacobSeq.size(); i++)
// 	{
// 		size_t jacobNo = _jacobSeq[i];
// 		size_t currLimit = std::min<size_t>(jacobNo, pending.size());
// 		std::cout << "jacob seq size: " << _jacobSeq[i] << ". pending size: " << pending.size() << ". currlimit: " << currLimit << std::endl; //debug

// 		std::cout << "6" << std::endl; //debug
// 		for (size_t j = currLimit; j > lastInsertedPos; j--)
// 		{
// 			Chain val = pending[j - 1];
// 			std::vector<Chain>::iterator insertLoc;
// 			insertLoc = std::lower_bound(main.begin(), main.end(), val.winner, comp);
// 			main.insert(insertLoc, val);
// 			std::cout << "6a" << std::endl; //debug
// 		}
// 		std::cout << "main size 2: " << main.size() << std::endl; //debug
// 		lastInsertedPos = currLimit;

// 		if (lastInsertedPos == pending.size())
// 			break ;
// 	}
// 	std::cout << "winner: ";
// 	for (size_t i = 0; i < main.size(); i++)
// 	{
// 		std::cout << " " << main[i].winner;
// 	}
// 	std::cout << std::endl;
// 	return (main);
// }
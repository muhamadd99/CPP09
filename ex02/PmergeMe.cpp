/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbani-ya <mbani-ya@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 18:51:45 by mbani-ya          #+#    #+#             */
/*   Updated: 2026/03/09 12:59:19 by mbani-ya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <cstddef>
#include <iostream>
#include <iterator>
#include <sys/time.h>
#include <algorithm>
#include <sstream>

PmergeMe::PmergeMe() : _compareVec(0), _compareDeq(0)
{}

PmergeMe::PmergeMe(const PmergeMe& other) : _nbrVec(other._nbrVec), _compareVec(0),
			_durationVec(0),  _compareDeq(0), _durationDeq(0)
{}

PmergeMe& PmergeMe::operator=(const PmergeMe& other) 
{
	if (this != &other)
	{
		_nbrVec = other._nbrVec;
		_compareVec = other._compareVec;
		_compareDeq = other._compareDeq;
		_durationVec = other._durationVec;
		_durationDeq = other._durationDeq;
	}
	return *this;
}

PmergeMe::~PmergeMe()
{}

void PmergeMe::runPrint(int ac, char **av)
{
	if (parseVector(ac, av)) return ;
	processVec();
	
	parseDeque(ac, av);
	processDeq();
	
	std::cout << "Before: "; printVector(_nbrVec);

	std::cout << "After: "; printVector(_sortedVec);
	
	std::cout << "Vector No of comparisons: " << _compareVec << std::endl;

	std::cout << "Before: "; printDeque(_nbrDeq);

	std::cout << "After: "; printDeque(_sortedDeq);
	
	std::cout << "Deque No of comparisons: " << _compareDeq << std::endl;
	
	std::cout << "Time to process a range of " << _nbrVec.size() << " elements with std::vector : " << _durationVec << " us" << std::endl;
	
	std::cout << "Time to process a range of " << _nbrDeq.size() << " elements with std::deque : " << _durationDeq << " us" << std::endl;

}

int PmergeMe::parseVector(int ac,  char **av)
{
	if (ac == 1)
	{
		printErr("No Input");
		return 1;
	}
	else if (ac == 2)
	{
		std::stringstream ss(av[1]);
		std::string tmp;

		while (ss >> tmp)
		{
			if (!strdigit(tmp.c_str()))
			{
				printErr("Wrong Input");
				return 1;
			}
			_nbrVec.push_back(atoi(tmp.c_str()));
		}
		if (_nbrVec.size() == 1)
			std::cout << _nbrVec[0] << std::endl;
	}
	else
	{
		for (int i = 1; av[i]; i++)
		{
			if (!strdigit(av[i]))
			{
				printErr("Wrong Input");
				return 1; 
			}
			else
				_nbrVec.push_back(atoi(av[i]));
		}
	}
	return 0;
}

void PmergeMe::processVec()
{
	struct timeval start, end;
	
	gettimeofday(&start, NULL);
	
	makeJacobVec();
	chainVec number;
	chainVec sorted;
	for (size_t i = 0; i < _nbrVec.size(); i++)
	{
		ChainV c;
		c.winner = _nbrVec[i];
		number.push_back(c);
	}
	sorted = recurse(number);
	for (size_t i = 0; i < sorted.size(); i++)
		_sortedVec.push_back(sorted[i].winner);
	
	gettimeofday(&end, NULL);
	long startUsec	= (start.tv_sec * 1000000) + start.tv_usec;
	long endUsec	= (end.tv_sec * 1000000) + end.tv_usec;
	_durationVec	= endUsec - startUsec;
}

//the limit is 10923
void PmergeMe::makeJacobVec()
{
	_jacobVec.clear();
	_jacobVec.push_back(3);
	_jacobVec.push_back(5);
	
	int nbr = 0;
	while (_jacobVec.back() < 10923)
	{
		nbr = _jacobVec.back() + (2 * _jacobVec[_jacobVec.size() - 2]);
		_jacobVec.push_back(nbr);
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

chainVec	PmergeMe::recurse(chainVec tmp)
{
	if (tmp.size() <= 1)
		return tmp;

	bool		hasOdd = (tmp.size() % 2 != 0);
	ChainV		oddChain;
	chainVec	newLvl = createNewLvl(tmp, hasOdd, oddChain);

	newLvl = recurse(newLvl);

	chainVec	main;
	chainVec	pending;
	
	preJacob(newLvl, main, pending, hasOdd, oddChain);
	insertJacob(main, pending);
	
	return main;
}

chainVec	PmergeMe::createNewLvl(chainVec& tmp, bool& hasOdd, ChainV& oddChain)
{
	chainVec	newLvl;

	if (hasOdd)
	{
		oddChain = tmp.back();
		tmp.pop_back();
	}
	for (size_t i = 0; i < tmp.size(); i += 2)
	{
		_compareVec++;
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
	return newLvl;
}

void	PmergeMe::preJacob(chainVec& newLvl, chainVec& main, chainVec& pending, bool hasOdd, ChainV& oddChain)
{
	for (size_t i = 0; i < newLvl.size(); i++)
	{
		pending.push_back(newLvl[i].losers.back());
		pending[i].pos = i;
		newLvl[i].losers.pop_back();
		main.push_back(newLvl[i]);
	}
	if (hasOdd)
	{
		oddChain.pos = main.size();
		pending.push_back(oddChain);
	}
}

void	PmergeMe::insertJacob(chainVec& main, chainVec& pending)
{
	if (!pending.empty())
	{
		main.insert(main.begin(), pending[0]);
		updatePos(pending, 0);
	}

	size_t		lastInsertedPos = 1;
	ComparatorV	comp(_compareVec);

	for (size_t i = 0; i < _jacobVec.size(); i++)
	{
		size_t	jacobNo = _jacobVec[i];
		size_t	currLimit = std::min<size_t>(jacobNo, pending.size());
		
		for (size_t j = currLimit; j > lastInsertedPos; j--)
		{
			ChainV				target	  = pending[j - 1];
			chainVec::iterator	limit	  = main.begin() + pending[j - 1].pos;
			chainVec::iterator	insertLoc = std::lower_bound(main.begin(), limit, target.winner, comp);

			size_t	insertIdx = std::distance(main.begin(), insertLoc);
			main.insert(insertLoc, target);
			updatePos(pending, insertIdx);
		}
		lastInsertedPos = currLimit;

		if (lastInsertedPos == pending.size())
			break ;
	}
}

void PmergeMe::updatePos(chainVec& pending, size_t insertIdx)
{
	for (size_t k = 0; k < pending.size(); k++)
		if (pending[k].pos >= insertIdx)
			pending[k].pos++;
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

int PmergeMe::parseDeque(int ac, char **av)
{
	if (ac == 1)
	{
		printErr("No Input");
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
				printErr("Wrong Input");
				return 1;
			}
			_nbrDeq.push_back(atoi(tmp.c_str()));
		}
		if (_nbrDeq.size() == 1)
			std::cout << _nbrDeq[0] << std::endl;
	}
	else
	{
		for (int i = 1; av[i]; i++)
		{
			if (!strdigit(av[i]))
			{
				printErr("Wrong Input");
				return 1;
			}
			else
				_nbrDeq.push_back(atoi(av[i]));
		}
	}
	return 0;
}

void PmergeMe::processDeq()
{
	struct timeval start, end;
	
	gettimeofday(&start, NULL);
	
	makeJacobDeq();
	chainDeq number;
	chainDeq sorted;
	for (size_t i = 0; i < _nbrDeq.size(); i++)
	{
		ChainD c;
		c.winner = _nbrDeq[i];
		number.push_back(c);
	}
	sorted = recurse(number);
	for (size_t i = 0; i < sorted.size(); i++)
		_sortedDeq.push_back(sorted[i].winner);
	
	gettimeofday(&end, NULL);
	long startUsec	= (start.tv_sec * 1000000) + start.tv_usec;
	long endUsec	= (end.tv_sec * 1000000) + end.tv_usec;
	_durationDeq	= endUsec - startUsec;
}

//the limit is 10923
//Formula: n + (2 * (n-1))
void PmergeMe::makeJacobDeq()
{
	_jacobDeq.clear();
	_jacobDeq.push_back(3);
	_jacobDeq.push_back(5);
	
	int nbr = 0;
	while (_jacobDeq.back() < 10923)
	{
		nbr = _jacobDeq.back() + (2 * _jacobDeq[_jacobDeq.size() - 2]);
		_jacobDeq.push_back(nbr);
	}
	return ;
}

chainDeq	PmergeMe::recurse(chainDeq tmp)
{
	if (tmp.size() <= 1)
		return tmp;
	
	bool		hasOdd = (tmp.size() % 2 != 0);
	ChainD		oddChain;
	chainDeq	newLvl = createNewLvl(tmp, hasOdd, oddChain);

	newLvl =  recurse(newLvl);

	chainDeq	main;
	chainDeq	pending;

	preJacob(newLvl,  main,  pending,  hasOdd, oddChain);
	insertJacob(main, pending);

	return main;
}

chainDeq	PmergeMe::createNewLvl(chainDeq& tmp, bool& hasOdd, ChainD& oddChain)
{
	chainDeq	newLvl;

	if (hasOdd)
	{
		oddChain = tmp.back();
		tmp.pop_back();
	}
	for (size_t i = 0; i < tmp.size(); i += 2)
	{
		_compareDeq++;
		if (tmp[i].winner > tmp[i + 1].winner)
		{
			tmp[i].losers.push_back(tmp[i + 1]);
			newLvl.push_back(tmp[i]);
		}
		else 
		{
			tmp[i + 1].losers.push_back(tmp[i]);
			newLvl.push_back(tmp[i +  1]);
		}
	}
	return newLvl;
}

void	PmergeMe::preJacob(chainDeq& newLvl, chainDeq& main, chainDeq& pending, bool hasOdd, ChainD& oddChain)
{
	for (size_t i = 0; i < newLvl.size(); i++)
	{
		pending.push_back(newLvl[i].losers.back());
		pending[i].pos = i;
		newLvl[i].losers.pop_back();
		main.push_back(newLvl[i]);
	}
	if (hasOdd)
	{
		oddChain.pos = main.size();
		pending.push_back(oddChain);
	}
}

void	PmergeMe::insertJacob(chainDeq& main, chainDeq& pending)
{
	if (!pending.empty())
	{
		main.insert(main.begin(), pending[0]);
		updatePos(pending, 0);
	}
	size_t		lastInsertedPos = 1;
	ComparatorD	comp(_compareDeq);

	for (size_t i = 0; i < _jacobDeq.size(); i++)
	{
		size_t	jacobNo = _jacobDeq[i];
		size_t	currLimit = std::min<size_t>(jacobNo, pending.size());

		for (size_t j = currLimit; j > lastInsertedPos; j--)
		{
			ChainD				target	  = pending[j - 1];
			chainDeq::iterator	limit	  = main.begin() + pending[j - 1].pos;
			chainDeq::iterator	insertLoc = std::lower_bound(main.begin(), limit, target.winner, comp);
			size_t				insertIdx = std::distance(main.begin(), insertLoc);
			main.insert(insertLoc, target);
			updatePos(pending,insertIdx);
		}
		lastInsertedPos =  currLimit;
		if (lastInsertedPos ==  pending.size())
			break ;
	}
}

void	PmergeMe::updatePos(chainDeq& pending, size_t insertIdx)
{
	for (size_t k = 0; k < pending.size(); k++)
		if (pending[k].pos >= insertIdx)
			pending[k].pos++;
}

void	PmergeMe::printErr(std::string str)
{
	std::cerr << "Error: " << str << std::endl;
}

void PmergeMe::printDeque(const std::deque<int>& deq)
{
	for (size_t i = 0; i < deq.size(); ++i)
	{
		std::cout << deq[i];
		std::cout << " ";
	}
	std::cout << std::endl;
}

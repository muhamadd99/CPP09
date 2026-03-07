/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbani-ya <mbani-ya@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 18:51:50 by mbani-ya          #+#    #+#             */
/*   Updated: 2026/03/07 13:59:51 by mbani-ya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <vector>
#include <deque>
#include <string>

struct Chain
{
	int					winner;
	std::vector<Chain>	losers;
	size_t				pos;
	bool operator<(const Chain& other) const
	{
		return winner < other.winner;
	}
};

struct Comparator
{
	size_t &count;

	Comparator(size_t& c) : count(c) {}
	
	bool operator()(const Chain& other, int value) const
	{
		count++;
		return other.winner < value;
	}
};

class PmergeMe {
private:
//			VECTOR
	std::vector<int> _nbr;
	std::vector<int> _jacobSeq;
	std::vector<int> _sortedVec;
//			DEQUE
	std::deque<int> _nbrDeque;
	size_t	_comparison;
public:
	PmergeMe();
	PmergeMe(const PmergeMe& other);
	PmergeMe& operator=(const PmergeMe& other);
	~PmergeMe();

	int		strdigit(const char* str);
	//				VECTOR
	std::vector<Chain>	recurse(std::vector<Chain> tmp);
	//std::vector<int>	recurse(std::vector<int> tmp);
	void	runVector(int ac, char **av);
	void	processVec();
	void	makeJacobSeq();
	void	printErr(std::string str);
	void	printVector(const std::vector<int>& vec);
	static bool	chainCompare(const Chain& other, int value);
	//				DEQUE
	void	runDeque(int ac,  char **av);
	void	printDeque(const std::deque<int>& deq);
	void	processDeque(); //not finished yet
};

#endif
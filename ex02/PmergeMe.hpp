/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbani-ya <mbani-ya@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 18:51:50 by mbani-ya          #+#    #+#             */
/*   Updated: 2026/03/09 18:11:43 by mbani-ya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <vector>
#include <deque>
#include <string>

struct ChainV
{
	int					winner;
	std::vector<ChainV>	losers;
	size_t				pos;
};

struct ComparatorV
{
	size_t &count;

	ComparatorV(size_t& compareVec) : count(compareVec) {}
	
	bool operator()(const ChainV& other, int targetValue) const
	{
		count++;
		return other.winner < targetValue;
	}
};

struct ChainD
{
	int					winner;
	std::deque<ChainD>	losers;
	size_t				pos;
};

struct ComparatorD
{
	size_t &count;

	ComparatorD(size_t& compareDeq) : count(compareDeq) {}
	
	bool operator()(const ChainD& other, int targetValue) const
	{
		count++;
		return other.winner < targetValue;
	}
};

typedef std::vector<ChainV> chainVec;
typedef std::deque<ChainD>  chainDeq;

class PmergeMe {
private:
//			VECTOR
	std::vector<int>	_nbrVec;
	std::vector<int>	_jacobVec;
	std::vector<int>	_sortedVec;
	size_t				_compareVec;
	double				_durationVec;

//			DEQUE
	std::deque<int>		_nbrDeq;
	std::deque<int>		_jacobDeq;
	std::deque<int>		_sortedDeq;
	size_t				_compareDeq;
	double				_durationDeq;

public:
	PmergeMe();
	PmergeMe(const PmergeMe& other);
	PmergeMe& operator=(const PmergeMe& other);
	~PmergeMe();

	int		strdigit(const char* str);
	void	runPrint(int ac, char **av);
	void	printErr(std::string str);

	//				VECTOR
	int			parseVector(int ac, char **av);
	void		processVec();
	void		makeJacobVec();
	chainVec	recurse(chainVec tmp);
	chainVec	createNewLvl(chainVec& tmp, bool& hasOdd, ChainV& oddChain);
	void		preJacob(chainVec& newLvl, chainVec& main, chainVec& pending, bool hasOdd, ChainV& oddChain);
	void		insertJacob(chainVec& main, chainVec& pending);
	void		updatePos(chainVec& pending, size_t insertIdx);
	void		printVector(const std::vector<int>& vec);

	//				DEQUE
	int			parseDeque(int ac,  char **av);
	void		processDeq();
	void		makeJacobDeq();
	chainDeq	recurse(chainDeq tmp);
	chainDeq	createNewLvl(chainDeq& tmp, bool& hasOdd, ChainD& oddChain);
	void		preJacob(chainDeq& newLvl, chainDeq& main, chainDeq& pending, bool hasOdd, ChainD& oddChain);
	void		insertJacob(chainDeq& main, chainDeq& pending);
	void		updatePos(chainDeq& pending, size_t insertIdx);
	void		printDeque(const std::deque<int>& deq);
};

#endif
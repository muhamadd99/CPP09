/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbani-ya <mbani-ya@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 18:51:50 by mbani-ya          #+#    #+#             */
/*   Updated: 2026/03/03 18:27:54 by mbani-ya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <vector>

class PmergeMe {
private:
	std::vector<int> _nbr;
	std::vector<int> _jacobSeq;
public:
	PmergeMe(std::vector<int>& nbr);
	PmergeMe(const PmergeMe& other);
	PmergeMe& operator=(const PmergeMe& other);
	~PmergeMe();

	void	process();
	void	recurse(std::vector<int> tmp);
	void	makeJacobSeq();
	static void	printVector(const std::vector<int>& vec);
};

#endif
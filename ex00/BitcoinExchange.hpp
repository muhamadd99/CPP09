/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbani-ya <mbani-ya@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 15:56:27 by mbani-ya          #+#    #+#             */
/*   Updated: 2026/03/01 15:26:36 by mbani-ya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <string>
#include <map>

class BitcoinExchange {
private:
	std::string _filePath;
	std::map<std::string, float> _bitcoinRate;
	std::string	_date;
	float _value;
public:
	BitcoinExchange(std::string file);
	BitcoinExchange(const BitcoinExchange& other);
	BitcoinExchange& operator=(const BitcoinExchange& other);
	~BitcoinExchange();
	int 	checkInput();
	int		parseRate();
	int		checkDate(std::string date);
	int		checkValue(std::string valueStr);
	void	getResult();
	int		strdigit(std::string str);
	int		strdigit2(std::string str);
};

#endif
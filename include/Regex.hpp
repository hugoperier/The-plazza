//
// EPITECH PROJECT, 2018
// slave
// File description:
// hpp
//

#pragma once

#include "Parser.hpp"
#include "Slave.hpp"
#include <regex>

void    pexit(std::string const &);

class Regex
{
public:
	Regex(std::string);
	~Regex();
	void start();

private:
	std::string _request;
	Information _info;
	std::string _file;
	void found(std::regex, std::string);
};

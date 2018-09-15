//
// EPITECH PROJECT, 2018
// plazza
// File description:
// parser
//

#include "Parser.hpp"
#include <iostream>

Plazza::Parser::Parser(void)
{
	_i = 0;
	_y = 0;
}

Plazza::Parser::~Parser(void)
{

}

void    Plazza::Parser::Parse(std::string &lines, char delim)
{
	std::vector<std::string> lineCutted = split(lines, delim);
	std::vector<std::string> commands;

	_i = 0;
	_y = 0;
	this->_commands.clear();
	for (auto &m : lineCutted) {
		m = cleanSpace(m);
		this->_commands.push_back(this->ParseLine(m));
	}
}

void	Plazza::Parser::print_commands()
{
	int	m = 0;

	for (auto &i : this->_commands){
		std::cout << "fichier : ";
		for (auto &c : i.first) {
			std::cout << c << " - ";
			m++;
		}
		std::cout << " | info to get : " << i.second << "\n";
	}
}

std::pair<std::vector<std::string>, std::string>
Plazza::Parser::ParseLine(
	std::string &line)
{
	std::vector<std::string>	files;
	std::string			info;
	std::vector<std::string>	lineSplitted = split(line, ' ');
	std::pair<std::vector<std::string>, std::string> group;

	if (lineSplitted.back() == "")
		lineSplitted.pop_back();
	for (auto &i : lineSplitted) {
		if (i == lineSplitted.back())
			info = i;
		else
			files.push_back(i);
	}
	group.first = files;
	group.second = info;
	return group;
}

std::pair<std::string, std::string> Plazza::Parser::getNextInstruction()
{
	std::pair<std::string, std::string> duo;

	while (_y < (int) this->_commands.size()) {
		while (_i < (int) this->_commands[_y].first.size()) {
			duo.first = this->_commands[_y].first[_i];
			duo.second = this->_commands[_y].second;
			_i++;
			return (duo);
		}
		_y++;
		_i = 0;
	}
	duo.first = "NULL";
	_i = 0;
	_y = 0;
	return duo;
}

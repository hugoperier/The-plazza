//
// EPITECH PROJECT, 2018
// plazza
// File description:
// header parser
//

#ifndef _PARSER_HPP
# define _PARSER_HPP

#include <vector>
#include <string>
#include <algorithm> // for iterator

enum Information
{
	PHONE_NUMBER,
	EMAIL_ADDRESS,
	IP_ADDRESS
};


std::vector<std::string>        split(std::string &, const char);
bool				contain(std::string const &, std::string const &);
std::string			cleanSpace(std::string const &);


namespace Plazza
{
	        class Parser
		{
		public:
			Parser(void);
			~Parser(void);
			void    Parse(std::string &lines, char delim);
			std::pair<std::string, std::string> getNextInstruction();
		private:
			std::vector<std::pair<std::vector<std::string>, std::string>> _commands;
			int	_i;
			int	_y;
			std::pair<std::vector<std::string>, std::string>
			ParseLine(std::string &);
			void	print_commands();
		};
};

#endif /* _PARSER_HPP */

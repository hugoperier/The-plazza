//
// EPITECH PROJECT, 2018
// plaza
// File description:
// header plaza
//

#ifndef _PLAZZA_HPP
# define _PLAZZA_HPP

#pragma once

#include "Slave.hpp"
#include "Namedpipe.hpp"
#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <list>
#include <stdexcept>
#include <algorithm>
#include <unordered_map>
#include <tuple>
#include <vector>
#include <signal.h>
#include <sys/types.h>
#include "Parser.hpp"

/*
** StringFunc functions
*/

std::vector<std::string>        split(std::string &, char);
bool				contain(std::string const &, std::string const &);
std::string			cleanSpace(std::string const &);
std::string			removeFromChar(std::string const, std::string const &);

namespace Plazza
{
	class InfoPlazza {
	public:
		InfoPlazza(int nb_thread);
		~InfoPlazza();
		void    WaitCommand();
	private:
		unsigned int		_nbThread;
		std::vector<Slave *>	_slave;
		std::vector<NamedPipe>	_namedPipes;
		void			readRapport();
		void			PrintSlave(std::string const &, const int);
		void			distribInstruct(Parser);
		int			getSlaveAvailable();
		int			getNbThreadUsedById(int);
		void			giveInstructionById(
			int id, std::pair<std::string, std::string> duo);
		void			sendQuery(std::string const &, const char *);
		std::string		readResponse(std::string);
		void			checkSlaveCreate();
		void			destroySlave();
	};
};

#endif /* !_PLAZZA_HPP */

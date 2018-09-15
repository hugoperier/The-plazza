//
// EPITECH PROJECT, 2018
// slave
// File description:
// hpp
//

#ifndef SLAVE
#define SLAVE

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <vector>
#include <fstream>
#include <utility>
#include "Threadcore.hpp"
#include "Namedpipe.hpp"

void    pexit(std::string const &);

class Slave
{
public:
	Slave(int, int);
	~Slave();
	void	start();

private:
	unsigned int			_maxThread;
	int				_id;
	std::vector<Threadcore *>	_threadPool;
	NamedPipe			_namedPipe;
	void				work();
	std::string			getQuery(std::string);
	void				sendResponse(std::string);
	std::string			get_thread();
	std::string			getNbThreadFree();
	std::string			giveInstructionToThread(std::string);
	void                            launchThread(unsigned int);
	void				removeAllThread();
};

#endif

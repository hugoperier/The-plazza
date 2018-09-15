//
// EPITECH PROJECT, 2018
// namedpipe
// File description:
// protocol
//

#ifndef NAMEDPIPE
#define NAMEDPIPE

#include <string>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

class NamedPipe
{
public:
	NamedPipe(int);
	NamedPipe() {}
	~NamedPipe();
	void		sendData(const std::string &);
	std::string	readData();

private:
	std::string	_fileName;
};

#endif

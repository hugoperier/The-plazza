//
// EPITECH PROJECT, 2018
// namedpipe
// File description:
// protocol communication
//

#include "Namedpipe.hpp"

NamedPipe::NamedPipe(int id)
{
	this->_fileName = "./app/slave" + std::to_string(id);
	if (access(this->_fileName.c_str(), O_WRONLY) != 0) {
		mkfifo(this->_fileName.c_str(), 0666);
	}
}

NamedPipe::~NamedPipe()
{
}

void	NamedPipe::sendData(const std::string &query)
{
	std::fstream	fs;

	//std::cout << "send "<< query << "\n";
	fs.open(this->_fileName, std::fstream::in | std::fstream::out | std::fstream::app);
	fs << query << "\n";
	fs.close();
}


std::string	NamedPipe::readData()
{
	std::fstream    fs;
	std::string     line = "";
	std::string     querry = "";

	fs.open(this->_fileName, std::fstream::in | std::fstream::out | std::fstream::app);
	std::getline(fs, line);
	querry += line;
	fs.close();
	//std::cout << "receive "<< querry << "\n";
	return querry;
}

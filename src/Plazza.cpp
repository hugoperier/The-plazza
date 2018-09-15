//
// EPITECH PROJECT, 2018
// plazza
// File description:
// plazza
//

#include "Plazza.hpp"

Plazza::InfoPlazza::InfoPlazza(int nb_thread)
{
	_nbThread = nb_thread;
}

Plazza::InfoPlazza::~InfoPlazza()
{

}

void Plazza::InfoPlazza::WaitCommand()
{
	std::string lines;
	Plazza::Parser p;

	while (std::getline(std::cin, lines)) {
		if (lines == "exit")
			break ;
		else if (lines == "debug")
			readRapport();
		else if (!lines.empty()) {
			p.Parse(lines, ';');
			distribInstruct(p);
		}
	}
	for (unsigned int i = 0; i < this->_slave.size(); ++i) {
		this->_namedPipes[i].sendData("stop");
	}
}

void	Plazza::InfoPlazza::readRapport()
{
	unsigned int	i = 0;
	std::string	response;

	for (i = 0; i < this->_slave.size(); ++i) {
		response = "";
		this->_namedPipes[i].sendData("debug");
		response = this->_namedPipes[i].readData();
		replace(response.begin(), response.end(), '|', '\n');
		std::cout << response;
	}
}

void		Plazza::InfoPlazza::distribInstruct(Parser p)
{
	std::pair<std::string, std::string> duo = p.getNextInstruction();
	int				    slaveId;

	if (duo.first == "NULL")
		std::cout << "[" << duo.first << "][" << duo.second << "]\n;";
	while (duo.first != "NULL") {
		checkSlaveCreate();
		slaveId = getSlaveAvailable();
		if (slaveId == -1) {
			std::cout << "Bad SlaveID\n";
			break;
		}
		giveInstructionById(slaveId, duo);
		usleep(200);
		duo = p.getNextInstruction();
	}
}

void	Plazza::InfoPlazza::checkSlaveCreate()
{
	int		totThreadFree = 0;
	static int	id = 0;

	for (unsigned int i = 0; i < this->_slave.size(); ++i)
		totThreadFree += getNbThreadUsedById(i);
	if (totThreadFree == 0) {
		Slave	*newSlave = new Slave(this->_nbThread, id);
		NamedPipe pipe(this->_slave.size());
		this->_namedPipes.push_back(pipe);
		this->_slave.push_back(newSlave);
		newSlave->start();
		usleep(5000);
		id++;
	}

}

void	Plazza::InfoPlazza::giveInstructionById(int id, std::pair<std::string, std::string> duo)
{
	std::string concat = duo.first + ";" + duo.second;

	usleep(3000);
	this->_namedPipes[id].sendData(concat.c_str());
	this->_namedPipes[id].readData();
}

int	Plazza::InfoPlazza::getSlaveAvailable()
{
	int	nbThreadFree;
	int	minThreadFree = 0;
	int	idMinima = -1;

	for (unsigned int i = 0; i < this->_slave.size(); ++i) {
		usleep(3000);
		nbThreadFree = getNbThreadUsedById(i);
		if (nbThreadFree > minThreadFree) {
			idMinima = i;
			minThreadFree = nbThreadFree;
		}
	}
	return idMinima;
}

int		Plazza::InfoPlazza::getNbThreadUsedById(int id)
{
	std::string fileName = "./app/slave" + std::to_string(id);
	std::string response;

	this->_namedPipes[id].sendData("nbthreadfree");
	response = this->_namedPipes[id].readData();
	return atoi(response.c_str());
}

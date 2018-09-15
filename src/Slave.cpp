//
// EPITECH PROJECT, 2018
// slave
// File description:
// simple process
//

#include "Slave.hpp"
#include "Plazza.hpp"

Slave::Slave(int nbThread, int id)
{
	this->_maxThread = nbThread;
	this->_id = id;
	this->_namedPipe = NamedPipe(id);
}

Slave::~Slave()
{

}

void	Slave::start()
{
	int	pid;

	if ((pid = fork()) == -1)
		pexit("fork failed");
	if (pid == 0)
		this->work();
	return ;
}

void	Slave::work()
{
	std::string query;
	std::string response;
	std::string path = "./app/slave" + std::to_string(this->_id);

	while (1) {
		query = this->_namedPipe.readData();
		if (query == "stop")
			break ;
		else if (query == "debug")
			response = get_thread();
		else if (query == "nbthreadfree") {
			response = getNbThreadFree();
		}
		else if (contain(query, ";")) {
			response = giveInstructionToThread(query);
		}
		this->_namedPipe.sendData(response);
	}
	removeAllThread();
	exit(0);
}

void		Slave::removeAllThread()
{
	for (unsigned int i = 0; i < this->_threadPool.size(); ++i) {
		this->_threadPool[i]->setEnd(1);
		this->_threadPool[i]->_thr.join();
	}
}

std::string	Slave::giveInstructionToThread(std::string query)
{
	Threadcore	*thc;

	for (unsigned int b = 0; b <= this->_maxThread; ++b) {
		if (b < this->_threadPool.size() &&
		    this->_threadPool[b]->getState() == SLEEP) {
			//std::cout << "using sleep thread\n";
			this->_threadPool[b]->setQuery(query);
			this->_threadPool[b]->setState(ACTIVE);
			return "ok";
		}
		else if (b > this->_threadPool.size()) {
			//std::cout << "using new thread\n";
			thc = new Threadcore(query, b - 1);
			thc->setState(ACTIVE);
			this->_threadPool.push_back(thc);
			usleep(5000);
			return "ok";
		}
	}
	return "pas ok";
}

std::string	Slave::getQuery(std::string fileName)
{
	std::fstream	fs;
	std::string	line = "";
	std::string	querry = "";

	fs.open(fileName, std::fstream::in | std::fstream::out | std::fstream::app);
	std::getline(fs, line);
	while (line != "end") {
		querry += line;
		std::getline(fs, line);
	}
	fs.close();
	return querry;
}

std::string	Slave::getNbThreadFree()
{
	int	free = 0;
	unsigned int i = 0;

	for (; i < this->_maxThread; i++) {
		if (i >= this->_threadPool.size()) {
			free++;
		}
		else if (this->_threadPool[i]->getState() == SLEEP) {
			free++;
		}
	}
	return (std::to_string(free));
}

void	Slave::sendResponse(std::string response)
{
	int	fd;
	std::string path = "./app/slave" + std::to_string(this->_id);

	fd = open(path.c_str(), O_WRONLY);
	if (fd == -1)
		pexit("cant open fifo file");
	dprintf(fd, "%s\nend\n", response.c_str());
	close(fd);
}

std::string	Slave::get_thread()
{
	std::string	line = "slave" + std::to_string(this->_id) + "|";
	unsigned int	i = 0;

	for (; i < this->_maxThread; i++) {
		line += "Thread[" + std::to_string(i) + "] : ";
		if (i >= this->_threadPool.size())
			line += "UNEXIST";
		else if (this->_threadPool[i]->getState() == ACTIVE)
			line += "ACTIVE";
		else if (this->_threadPool[i]->getState() == SLEEP)
			line += "SLEEP";
		line += "|";
		}
	return (line);
}

void	pexit(std::string const &msg)
{
	std::cerr << msg << std::endl;
}

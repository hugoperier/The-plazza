//
// EPITECH PROJECT, 2018
// thread
// File description:
// class
//

#include "Threadcore.hpp"
#include "Regex.hpp"

Threadcore::Threadcore(std::string query, int id)
{
	this->_request = query;
	this->_id = id;
	this->_state = ACTIVE;
	this->_thr = std::thread(&Threadcore::start, this);
	this->_end = 0;
}

Threadcore::~Threadcore()
{

}

void	Threadcore::start()
{
	while (!this->_end)
	if (this->_state == ACTIVE) {
		//std::cout << "regex: " << this->_request << "\n";
		Regex reg(this->_request);
		this->_state = SLEEP;
	}
}

void	Threadcore::setState(State state)
{
	this->_state = state;
}

State	Threadcore::getState()
{
	return this->_state;
}

void	Threadcore::setQuery(std::string querry)
{
	this->_request = querry;
}

void	Threadcore::setEnd(int end)
{
	this->_end = end;
}

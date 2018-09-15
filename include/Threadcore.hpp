//
// EPITECH PROJECT, 2018
// threadcore
// File description:
// th
//

#ifndef THREADCORE
#define THREADCORE

#include <iostream>
#include <string>
#include <unistd.h>
#include <thread>
#include <mutex>

enum State
{
	ACTIVE,
	SLEEP,
	UNSET
};

class Threadcore
{
public:
	Threadcore(std::string, int);
	~Threadcore();
	void		start();
	void		setState(State state);
	State		getState();
	void		setQuery(std::string);
	void		setEnd(int);
	std::thread	_thr;


private:
	std::string	_request;
	int		_id;
	int		_end;
	State		_state;
};

#endif

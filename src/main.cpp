//
// EPITECH PROJECT, 2018
// plazza
// File description:
// main.cpp
//

#include "Plazza.hpp"
#include "Parser.hpp"
#include <iostream>

int	main(int ac, char **av)
{
	if (ac < 2)
	{
		std::cerr << "Usage : ./plazza [number of thread]\n";
		return 1;
	}
	try
	{
		int thr = std::atoi(av[1]);
		if (thr <= 0)
			std::cerr << "number of thread must be positif" << std::endl;
		Plazza::InfoPlazza core(thr);
		core.WaitCommand();
	}
	catch (std::exception const &e)
	{
		std::cerr << "Error : " << e.what() << "\n";
		return 1;
	}
	return 0;
}

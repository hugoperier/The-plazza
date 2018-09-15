//
// EPITECH PROJECT, 2018
// string
// File description:
// Some string usable func
//

#include "Parser.hpp"

std::vector<std::string>	split(std::string &str, char delim)
{
	std::vector<std::string> strSplitted;
	std::string substr;
	size_t debut = 0;
	size_t fin;
	if (delim == ' ')
		str = cleanSpace(str);
	fin = str.find(delim);
	while (fin != std::string::npos) {
		substr = str.substr(debut, fin - debut);
		strSplitted.push_back(substr);
		debut = fin + 1;
		fin = str.find(delim, fin + 1);
	}
	substr = str.substr(debut, fin - debut);
	strSplitted.push_back(substr);
	return strSplitted;
}

bool	contain(std::string const &str, std::string const &what)
{
	if (str.find(what) != std::string::npos)
		return true;
	return false;
}

std::string	cleanSpace(std::string const &str)
{
	std::string newstr;
	bool prev = true;
	for (auto const &c : str) {
		if (c == '\t' || c == ' ') {
			if (!prev)
				newstr += ' ';
			prev = true;
		} else {
			newstr += c;
			prev = false;
		}
	}
	return newstr;
}

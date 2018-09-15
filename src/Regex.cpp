//
// EPITECH PROJECT, 2018
// thread
// File description:
// class
//

#include "Parser.hpp"
#include "Regex.hpp"

const std::vector<std::string>	split(const std::string& str, const char& c)
{
	std::string	buff = "";
	std::vector<std::string>	vec;

	for(auto n:str)
	{
		if(n != c)
			buff += n;
		else
			if(n == c && buff != "") {
				vec.push_back(buff);
				buff = "";
			}
	}
	if(buff != "")
		vec.push_back(buff);
	return vec;
}

Regex::Regex(std::string query) : _request(query)
{
	try {
		std::vector<std::string> vec = split(_request, ';');
		if (vec[1] == "PHONE_NUMBER")
			_info = PHONE_NUMBER;
		if (vec[1] == "EMAIL_ADDRESS")
			_info = EMAIL_ADDRESS;
		if (vec[1] == "IP_ADDRESS")
			_info = IP_ADDRESS;
		_file = vec[0];
		if (_info >= PHONE_NUMBER && _info <= IP_ADDRESS)
			this->start();
	}
	catch (std::exception const &e)
	{
		std::cerr << "Error : " << e.what() << "\n";
	}
}

Regex::~Regex()
{
}

void	Regex::start()
{
	std::regex mail("[a-zA-Z0-9_.-]+@[a-zA-Z0-9_.-]+");
	std::regex phone("(0\\ ?[0-9]\\ ?)(([0-9]\\ ?){2}){4}");
	std::regex ip("(?:(?:[0-9]|[1-9][0-9]|1[0-9][0-9]"
		      "|2[0-4][0-9]|25[0-5])\\.){3}(?:[0-9]"
		      "|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])");
	std::ifstream file(_file);
	std::string buff((std::istreambuf_iterator<char>(file)),
			 std::istreambuf_iterator<char>());
	if (_info == PHONE_NUMBER)
		this->found(phone, buff);
	if (_info == EMAIL_ADDRESS)
		this->found(mail, buff);
	if (_info == IP_ADDRESS)
		this->found(ip, buff);
}

void	Regex::found(std::regex reg, std::string buff)
{
	std::smatch	m;
	std::string	result = "";

	while (std::regex_search(buff, m, reg)) {
		result += m.str() + "\n";
		buff = m.suffix().str();
	}
	std::cout << result;
	usleep(500);
}

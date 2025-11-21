#ifndef DATA_HPP
#define DATA_HPP

#include <string>
#include <iostream>

struct Data {
	int			id;
	std::string name;
	double		value;

	Data();
	Data(int id, const std::string& name, double value);
	Data(const Data& copy);
	Data& operator=(const Data& other);
	~Data();

	void display() const;
};

#endif
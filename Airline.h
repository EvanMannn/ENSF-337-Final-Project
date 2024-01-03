#ifndef AIRLINE_CLASS
#define AIRLINE_CLASS

#include "Flight.h"
#include <string>

class Airline
{
public:
	Airline();
	Airline(string n, Flight f);

	string getName() const;
	void setName(string n);

	Flight getFlight() const;


private:
	string airLineName;
	Flight flight;
};
#endif 

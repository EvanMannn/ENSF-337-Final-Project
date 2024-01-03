#include "Airline.h"
#include "Flight.h"
#include <string>

Airline::Airline()
{
	airLineName = string("");
	flight = Flight();
}

Airline::Airline(string n, Flight f)
{
	airLineName = n;
	flight = f;
}

string Airline::getName() const
{
	return airLineName;
}
void Airline::setName(string n)
{
	airLineName = n;
}

Flight Airline::getFlight() const
{
	return flight;
}
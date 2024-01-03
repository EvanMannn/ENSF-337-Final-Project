#ifndef SEAT_CLASS
#define SEAT_CLASS

#include <string>
#include "Passenger.h"

class Seat
{
public:
	//Constructors
	Seat();
	Seat(unsigned int row, char seatColumn, int pID);
	Seat(unsigned int row, unsigned int seatColumn, int pID);


	//Setters
	void setSeatPos(unsigned int r, char c);
	void setPassengerID(int pID);

	//Getters
	unsigned int getRow() const;
	unsigned int getColIdx() const;
	char getColChar() const;
	int getPassID() const;

private:
	unsigned int row;
	unsigned int col;
	int passID;
};

#endif
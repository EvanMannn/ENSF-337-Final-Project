#include "Seat.h"
#include <stdio.h>

using namespace std;

//Constructors
Seat::Seat() : row{ 0 }, col { 0 }, passID { -1 }
{

}

Seat::Seat(unsigned int row, char seatColumn, int pID) : row{ row }, passID{ pID }
{
	col = ((int)seatColumn) - 65;
}

Seat::Seat(unsigned int row, unsigned int seatColumn, int pID = -1) : row{ row }, col{ seatColumn }, passID{ pID }
{

}

//Setters
void Seat::setSeatPos(unsigned int r, char c) 
{
	row = r;
	col = ((int)c) - 65;
}

void Seat::setPassengerID(int pID)
{
	passID = pID;
}

//Getters
unsigned int Seat::getRow() const
{
	return row;
}
unsigned int Seat::getColIdx() const
{
	return col;
}
char Seat::getColChar() const
{
	return (char)(col + 65);
}
int Seat::getPassID() const
{
	return passID;
}
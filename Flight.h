#ifndef FLIGHT_CLASS
#define FLIGHT_CLASS


#include <vector>
#include <string>
#include "Seat.h"
#include "Passenger.h"

using namespace std;

class Flight
{
public:
	//Constructors
	Flight();
	Flight(string name, unsigned int rows, unsigned int cols);



	//Getters
	unsigned int getRows();
	unsigned int getCols();
	unsigned int getTotalPassengers();
	Seat* getSeat(unsigned int r, unsigned int c);
	string getName();

	void displaySeatMap();
	void displayPassengerInfo();
	void addPassenger(Passenger p);
	void removePassenger(unsigned int pId);
	Passenger getPassenger(unsigned int idx);


private:
	unsigned int numRows;
	unsigned int numCols;
	unsigned int totalPassengers;
	vector < vector <Seat>> seatMap;
	string flightName;
	
	//Passenger linked list
	struct Node {
		Passenger data;
		Node* next;
	};

	Node* head;
};

#endif
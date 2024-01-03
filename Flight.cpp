#include "Flight.h"
#include <vector>
#include <string>
#include <assert.h>
#include <iostream>
#include <iomanip>
#include "Seat.h"
#include "Passenger.h"

using namespace std;
//Constructors
//Default constructor
Flight::Flight()
{
	flightName = string("");
	numRows = 0;
	numCols = 0;
	totalPassengers = 0;

	head = nullptr;
}

//Overloaded constructor
Flight::Flight(string name, unsigned int rows, unsigned int cols)
{
	flightName = name;
	numRows = rows;
	numCols = cols;
	totalPassengers = 0;

	//No passengers so the head of the linked list points to null
	head = nullptr;

	//resizing the vector of vectors of seats based on the rows and columns inputted
	seatMap.resize(numRows);
	for (unsigned int i = 0; i < numRows; i++)
	{
		seatMap[i].resize(numCols);
		for (unsigned int j = 0; j < numCols; j++)
		{
			seatMap[i][j] = Seat(i, j, -1);	//Seats with a negative 1 for the assigned passenger ID are unassigned 
		}
	}
}



//Getters
unsigned int Flight::getRows()
{
	return numRows;
}
unsigned int Flight::getCols()
{
	return numCols;
}
Seat* Flight::getSeat(unsigned int r, unsigned int c)
{
	return &seatMap[r][c];
}
string Flight::getName()
{
	return flightName;
}
unsigned int Flight::getTotalPassengers()
{
	return totalPassengers;
}

//Class Methods
//Display the flight seat map

/*
most of this function is just formatting the output to the terminal with labels for columns and rows
along side spacing each of the seats out
*/
void Flight::displaySeatMap()
{
	
	cout << "\nFlight Seat Map\n" << endl << "   ";
	
	for (int col = 0; col < numCols; col++)
		cout << "  " << (char)(col + 65) << " ";
	cout << endl;


	cout << setw(3) << " ";
	for (int col = 0; col < numCols; col++)
		cout << "+---";
	cout << "+\n";

	for (int row = 0; row < numRows; row++)
	{
		cout << left << setw(3) << row;
		for (int col = 0; col < numCols; col++)
		{
			cout << "| " << ((seatMap[row][col].getPassID() != -1) ? 'X' : ' ') << " ";
		}
		cout << "|" << endl;

		cout << setw(3) << " ";
		for (int col = 0; col < numCols; col++)
			cout << "+---";
		cout << "+\n";
		
	}
	cout << endl;
}



//Display the passenger information
/*
This function uses a node pointer cursor to loop over each of the elements of the ordered linked list
After each passenger has its formatted string printed to the terminal the cursor moves to the next passenger using the next variable of the current node
*/
void Flight::displayPassengerInfo()
{
	cout << endl;
	cout << left << setw(20) << "First Name" << setw(20) << "Last Name" << setw(20) << "Phone Number" << setw(5) << "Row" << setw(6) << "Seat" << setw(7) << "ID" << "\n";
	string spacer = string(78, '-');
	cout << spacer << endl;

	Node* cur;
	cur = head;
	while (cur != nullptr)
	{ 
		cur->data.DisplayInfo();
		cur = cur->next;
		
		cout << spacer << endl;
	}
	cout << endl;
}

//Adding a passenger to the linked list
/* 
The function takes a validated passenger object in as a argument and goes through the nesscesary steps to properly integrate its data into the ordered linked list
First it assigns its respective seat to the ID that it holds
Second, the linked list is looped over to find the place where its ID fits in with the lowest IDs at the start and the highest at the end
Special procedures are followed for if the linked list is empty or if the passenger is to be put at the end of the list
Total passengers are incremented by 1 if a passenger is added
*/
void Flight::addPassenger(Passenger p)
{
	//Assigning the seat ID
	for (unsigned int i = 0; i < numRows; i++)
	{
		for (unsigned int j = 0; j < numCols; j++)
		{
			if (i == p.getSeat().getRow() && j == p.getSeat().getColIdx())
				seatMap[i][j].setPassengerID(p.getID());
		}
	}

	//New passenger node creation
	Node* newPass = new Node;
	assert(newPass != nullptr);
	newPass->data = p;
	newPass->next = nullptr;

	
	//checking if the list is empty
	if (head == nullptr)
	{
		head = newPass;
		totalPassengers += 1;
		return;
	}
	
	//checking if the new passenger can go right at the front
	else if (head->data.getID() >= newPass->data.getID())
	{
		newPass->next = head->next;
		head = newPass;
		totalPassengers += 1;
		return;
	}
		
	//Looping over the entire list using the cursors before and after to find the position the new passenger fits into
	else {
		Node* before = head;
		Node* after = head->next;

		while (after != nullptr && newPass->data.getID() > after->data.getID())
		{
			before = after;
			after = after->next;
		}
		newPass->next = after;
		before->next = newPass;
		
	}
	//incrementing the total passengers added, this happens for the first two if conditions as well
	totalPassengers += 1;
}

//Remove a passenger based on its ID
/*
This function follows a similar process to the add passenger but is removing them from the list instead
It does the same checks to see if the list is currently empty, if head is currently looking at the passenger to remove or loops over the list to find the passenger
total passengers are decremented by 1 if a passenger is removed
*/
void Flight::removePassenger(unsigned int pId)
{
	Node* toDelete = nullptr;
	Node* before = head;
	Node* maybeDelete = head->next;

	if (head == nullptr)
		return;

	if (head != nullptr && pId == head->data.getID())
	{
		toDelete = head;
		head = head->next;
	}
	else {
		do {
			if (maybeDelete != nullptr && maybeDelete->data.getID() == pId)
			{ 
				toDelete = maybeDelete;
				before->next = maybeDelete->next;
			}
				
			before = maybeDelete;
			maybeDelete = maybeDelete->next;
		} while (maybeDelete != nullptr && toDelete == nullptr);
	}

	if (toDelete == nullptr) {
		cout << "Invalid Passeger ID\n\n";
		return;
	}


	if (toDelete->next == nullptr)
		before->next = nullptr;

	for (unsigned int i = 0; i < numRows; i++)
	{
		for (unsigned int j = 0; j < numCols; j++)
		{
			if (i == toDelete->data.getSeat().getRow() && j == toDelete->data.getSeat().getColIdx())
				seatMap[i][j].setPassengerID(-1);
		}
	}
	
	cout << "Passenger with ID: " << pId << " has been removed\n\n";
	//MAYBE A MEMORY LEAK CHECK WITH PROF but probably not 
	toDelete->next = nullptr;
	delete toDelete;
	totalPassengers -= 1;
	
}


//Index a passenger from the linked list, head points to index 0
Passenger Flight::getPassenger(unsigned int idx)
{
	unsigned int curIdx = 0;
	Node* cursor;
	cursor = head;
	while (curIdx != idx)
	{
		cursor = cursor->next;
		curIdx += 1;
	}
	return cursor->data;
}


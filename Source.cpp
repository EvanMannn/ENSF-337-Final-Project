#include "Flight.h"
#include <vector>
#include <fstream>
#include <string>
#include <assert.h>
#include <iostream>
#include <iomanip>
#include "Seat.h"
#include "Passenger.h"
#include "Airline.h"

using namespace std;

void saveDataToFile(string filename, Flight flight) {
	
	//Creating the file output stream and making sure the file was opened correctly
	ofstream outFile(filename);
	if (!outFile) {
		cout << "Error opening file." << endl;
		return;
	}

	//Outputing the first line which includes the flight name along with the number of rows and columns
	outFile << flight.getName() << "\t "<< flight.getRows() << "\t "<< flight.getCols() << endl;

	//Looping over each of the passengers in the flight class passed to the function and printing their data in a consistent format
	for (int i = 0; i < flight.getTotalPassengers(); i++) {
		outFile << left << setw(20) << flight.getPassenger(i).getFname();
		outFile << left << setw(20) << flight.getPassenger(i).getLname();
		outFile << left << setw(20) << flight.getPassenger(i).getPhoneNum();
		outFile << left << setw(4) << to_string(flight.getPassenger(i).getSeat().getRow()) + flight.getPassenger(i).getSeat().getColChar();
		outFile << left << setw(5) << flight.getPassenger(i).getID();
		outFile << endl;
	}

	outFile.close();
	cout << "All data in the passenger list was saved into the \"flight_info.txt\"\n\n";
}

void display_header()
{
	cout << "Version 1.0" << endl;
	cout << "Term Project - Flight Managment Project in C++" << endl;
	cout << "Produced By: Evan Mann, Trung Tuan Mai" << endl;
	cout << "Year: 2023\n" << endl;
}

void display_menu()
{
	cout << "Please select one of the following options:\n";
	cout << "1. Display Flight Seat Map\n";
	cout << "2. Display Passengers Information\n";
	cout << "3. Add a new Passenger\n";
	cout << "4. Remove an Existing Passenger\n";
	cout << "5. Save Data\n";
	cout << "6. Quit\n\n";
	cout << "Enter Your Choice (1, 2, 3, 4, 5 or 6) ";
}

Flight populate_flight_from_file(string fileName)
{
	//Create a input file stream from the filename passed to the function and check that is was opened correctly
	ifstream inFile(fileName);
	if (!inFile) {
		cout << "Error opening file." << endl;
		exit(1);
	}

	//Flight information variables read from the first line in the file
	string flightNumber;
	unsigned int numRows, numSeatsPerRow;
	inFile >> flightNumber >> numRows >> numSeatsPerRow;


	// Create a Flight object
	Flight flight(flightNumber, numRows, numSeatsPerRow);


	//Using get to move past the newline character in the first line
	char c;
	inFile.get(c);


	//Passenger information variables
	string fileLine;
	string firstName, lastName, phoneNumber, seatNumber;
	unsigned int passengerId, seatRow = 0, seatCol = 0;


	//A while loop that reads one full line of the file at a time. Each of the pieces of information that makes up a passenger follow a consistent format
	//meaning that this full line of the file can be parsed based on the size of each piece
	while (std::getline(inFile, fileLine)) {

		firstName = fileLine.substr(0, 20);
		lastName = fileLine.substr(20, 20);
		phoneNumber = fileLine.substr(40, 20);
		seatNumber = fileLine.substr(60, 4);
		passengerId = stoi(fileLine.substr(64, 5));

		//If statements used to check if the row number is one or two digits long then seperating that number and the seat character into two different varaiables
		if (seatNumber.find_first_not_of("0123456789") == 2)
		{
			seatRow = stoi(seatNumber.substr(0, 2));
			seatCol = (int)seatNumber.at(2) - 65;	//converting the character read into a column index
		}
		else if (seatNumber.find_first_not_of("0123456789") == 1)
		{
			seatRow = stoi(seatNumber.substr(0, 1));
			seatCol = (int)seatNumber.at(1) - 65;
		}


		//Adding a passenger to the flight based off what was read from the file
		flight.addPassenger(Passenger(firstName, lastName, phoneNumber, flight.getSeat(seatRow, seatCol), passengerId));
		
	}
	return flight;
}


int main(void)
{
	//Display the program header and pause until the user presses return
	display_header();
	cout << "<<< PRESS RETURN TO CONTINUE >>>\n";
	char pause;
	cin.get(pause);


	//Populate a flight with data from the provided txt file and create an airline object to house that flight
	Flight flight = populate_flight_from_file("flight_info.txt");
	Airline al = Airline(string("WestJet"), flight);


	
	/*
	This menu functions by using switch cases based on the users inputs that control the various function of the menu:
		- 1) Display the flight seat map using the displaySeatMap function within the flight class
		- 2) Display the passengers information using the displayPassengerInfo function within the flight class
		- 3) Add a new passenger by prompting the user for various inputs such as their name ID and seat then calling the addPassenger function of the flight class
		to add it to the linked list of passengers 
		- 4) Remove an existing passenger based on the ID inputted by the user
		- 5) Save the current flight data into the same file used to populate the flight at the beginning of the program
		- 6) Exit he program 
	
	Each of the inputs taken from the user are checked to make sure there are no errors such that the program doesn't crash and the user can continue. 
	These checks happen on every single input taken from the user. Along side this, correct inputs that could create errors are also handled such as:
		- Trying to remove passengers that don't exist
		- Trying to add a passenger with an ID that is taken
		- Trying to assign a passenger to a seat that is already taken
	*/


	string menu = string(' ', 1);
	bool runProgram = true;
	bool invalidOption = false;
	while (runProgram)
	{
		
		//Used to only display the menu if a valid option com
		if (!invalidOption)
		{
			display_menu();
		}

		getline(cin, menu);
		if (string(menu, 1).length() > 1)
			menu = string(' ', 1);

		//variables for making a new passenger
		string newID;
		string newFN;
		string newLN;
		string newPhone;
		string newRow;
		string newSeat;

		//Variable for the yes or no choice when prompted to save a file
		string saveFile;

		//Variable for the ID of the passenger requested to be removed
		string passengerIDtoRemove;

		//Input validation variables
		bool validInput = false;
		bool validSeat;

		switch (menu.at(0)) {

			//Display the seat map
		case '1':
			invalidOption = false;

			flight.displaySeatMap();
			break;

			//Display passenger information
		case '2':
			invalidOption = false;

			flight.displayPassengerInfo();
			break;

			//Add passenger
		case '3':
			invalidOption = false;


			//Reading and validating passenger ID input
			while (!validInput)
			{
				bool duplicateFound = false;

				cout << "Please enter the passenger ID (Please use only numbers and follow the format: XXXXX: ";
				getline(cin, newID);
				cout << endl;

				if (newID.length() == 5 && (newID.find_first_not_of("0123456789") == string::npos)) {}
				else
				{
					cout << "Invalid Input. Please use only numbers and follow the format: XXXXX\n";
					continue;
				}
					
				//Checking if the input is already taken
				for (int i = 0; i < flight.getRows(); i++)
					for (int j = 0; j < flight.getCols(); j++)
					{
						if (flight.getSeat(i, j)->getPassID() == stoi(newID))
						{
							cout << "Input was valid but a passenger with that ID is already assigned to a seat, please choose a different ID\n";
							duplicateFound = true;
						}
						else if (i == flight.getRows() - 1 && j == flight.getCols() - 1 && duplicateFound == false)
							validInput = true;
					}
				
			}

			//Reading and validating the first name
			validInput = false;
			while (!validInput)
			{
				cout << "Please enter the passenger first name: ";
				getline(cin, newFN);
				cout << endl;

				if (newFN.length() < 20)
					validInput = true;
				else
					cout << "Invalid Input. Please input a name that is only 11 characters or less\n";
			}

			//Reading and validating the last name
			validInput = false;
			while (!validInput)
			{
				cout << "Please enter the passenger last name: ";
				getline(cin, newLN);
				cout << endl;

				if (newLN.length() < 20)
					validInput = true;
				else
					cout << "Invalid Input. Please input a name that is only 11 characters or less\n";
			}

			//Reading and validating the phone number. It must be input as three numbers then a space, then three numbers, then a space, then the last four numbers
			validInput = false;
			while (!validInput)
			{
				cout << "Please enter the passenger phone number (Please use only numbers and follow the format: XXX XXX XXXX): ";
				getline(cin, newPhone);
				cout << endl;

				if (newPhone.length() != 12)
				{
					cout << "Invalid Input. Please use only numbers and follow the format: XXX XXX XXXX\n";
					continue;
				}

				while (true)
				{
					size_t place = newPhone.find_first_of(" ");
					if (place == string::npos)
						break;
					newPhone.erase(place, 1);
				}

				if (newPhone.find_first_not_of("0123456789") == string::npos)
				{
					validInput = true;
					newPhone.insert(3, 1, '-');
					newPhone.insert(7, 1, '-');
				}
				else 
					cout << "Invalid Input. Please use only numbers and follow the format: XXX XXX XXXX\n";
			}

			//Reading and validating the seat input
			validSeat = false;
			while (!validSeat)
			{
				//Row input
				validInput = false;
				while (!validInput)
				{
					cout << "Please enter the passenger's desired row (0 - " << flight.getRows() - 1 << "): ";
					getline(cin, newRow);
					cout << endl;

					if (newRow.find_first_not_of("0123456789") != string::npos)
					{
						cout << "Invalid Input. Please input a number between 0 and " << flight.getRows() - 1 << "\n";
						continue;
					}

					else if (stoi(newRow) < 0 || stoi(newRow) >= flight.getRows())
					{
						cout << "Invalid Input. Please input a number between 0 and " << flight.getRows() - 1 << "\n";
						continue;
					}

					else
						validInput = true;
				}

				//Seat input
				validInput = false;
				while (!validInput)
				{
					cout << "Please enter the passenger's desired seat (Single Capital Letters Only): ";
					getline(cin, newSeat);
					cout << endl;

					if (newSeat.length() > 1)
					{
						cout << "Invalid Input. Please input a single capital letter\n";
						continue;
					}

					else if (((int)newSeat.at(0)) - 65 >= flight.getCols() || ((int)newSeat.at(0)) - 65 < 0)
					{
						cout << "Invalid Input. Please input a single capital letter\n";
						continue;
					}

					validInput = true;
				}

				//Checking if the seat is taken
				if (flight.getSeat(stoi(newRow), ((int)newSeat.at(0)) - 65)->getPassID() != -1)
				{
					cout << "A valid seat has been inputted but that seat is already taken, please input a new seat\n";
					continue;
				}
				else
					validSeat = true;
					
			}

			//With all inputs validated a new passenger is added using the information provided
			flight.addPassenger(Passenger(newFN, newLN, newPhone, flight.getSeat(stoi(newRow), (int)(newSeat).at(0) - 65), stoi(newID)));
			break;

			//Remove passenger
		case '4':
			invalidOption = false;

			//Reading and validating the ID input. The ID must exist for it to be removed
			validInput = false;
			while (!validInput)
			{
				cout << "\nPlease input the ID of the passenger to be removed in the form XXXXX: ";
				getline(cin, passengerIDtoRemove);

				if (passengerIDtoRemove.length() != 5)
				{
					cout << "Invalid input. please input only digits in the form XXXXX";
					continue;
				}
				else if (passengerIDtoRemove.find_first_not_of("0123456789") != string::npos)
				{
					cout << "Invalid input. please input only digits in the form XXXXX";
					continue;
				}
				else {
					validInput = true;
				}
			}

			cout << endl;
			//Removing the passenger from the linked list
			flight.removePassenger(stoi(passengerIDtoRemove));
			break;

			//Saving the current flight data
		case '5':
			invalidOption = false;
			validInput = false;
			while (!validInput)
			{
				cout << "Do you want to save the data in the \"flight_info.txt\"? Please answer <Y or N> ";
				getline(cin, saveFile);
				cout << endl;
				if (saveFile == string("Y"))
				{
					
					saveDataToFile("flight_info.txt", flight);
					validInput = true;
				}
				else if (saveFile == string("N"))
				{
					cout << "Did not save data\n\n";
					validInput = true;
				}
				else
				{
					cout << "Invalid input. Please only input Y or N\n";
				}
			}
			break;

			//Exiting the program by changing the runProgram boolean variable to false such that the main function terminates
		case '6':
			invalidOption = false;

			cout << "Program Terminated";
			runProgram = false;
			break;

		default:
			cout << "Please enter a valid option (1, 2, 3, 4, 5 or 6) ";
			invalidOption = true;
		}
		
	}

	return 0;
}
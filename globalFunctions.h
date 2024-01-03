#ifndef GLOBAL_FUNCTIONS
#define GLOBAL_FUNCTIONS

#include <vector>
#include <string>
#include "Flight.h"

using namespace std;

//Main function of the program that handles all user inputs for controlling the program
int main(void);

//Function to return a new filled in flight class from an existing .txt file
Flight populate_flight_from_file(string fileName);

//Function to print the menu options
void display_menu();

//Function to display the program header
void display_header();

//Function to save a flights data to a .txt file
void saveDataToFile(string filename, Flight flight);

#endif
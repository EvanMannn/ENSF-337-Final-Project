#ifndef PASSENGER_CLASS
#define PASSENGER_CLASS

#include <vector>
#include <String>
class Seat;
using namespace std;

class Passenger
{
public:
	//Constructors
	Passenger();
	Passenger(string Fname, string Lname, string phoneNum, Seat* seatArg, unsigned int ID);
	~Passenger();


	//Setters
	void setFname(string fn);
	void setLname(string ln);
	void setPhoneNum(string pn);
	void assignSeat(Seat* seat);
	void setID(unsigned int id);


	//Getters
	string getFname() const;
	string getLname() const;
	string getPhoneNum() const;
	Seat getSeat() const;
	unsigned int getID() const;

	void DisplayInfo() const;

private:
	string Fname;
	string Lname;
	string phoneNum;
	Seat *seat;
	unsigned int ID;

};

#endif
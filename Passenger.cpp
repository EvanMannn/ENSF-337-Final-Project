#include "Passenger.h"
#include "Seat.h"
#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;
Passenger::Passenger(){
    Fname = string("");
    Lname = string("");
    phoneNum = string("");
    seat = nullptr;
    ID = -1;
}

Passenger::Passenger(string Fname, string Lname, string phoneNum, Seat* seatArg, unsigned int ID):Fname(Fname),Lname(Lname), phoneNum(phoneNum), seat(seatArg), ID(ID){
    seat->setPassengerID(ID);
}

Passenger::~Passenger(){
    //dummy code
}

void Passenger::setFname(string Fname){
    Fname = Fname;
}

void Passenger::setLname(string Lname){
    Lname = Lname;
}

void Passenger::setPhoneNum(string phoneNum){
    phoneNum = phoneNum;
}

void Passenger::assignSeat(Seat* seatArg){
    seat = seatArg;
}

void Passenger::setID(unsigned int IDarg){
    ID = IDarg;
}

string Passenger::getFname() const{
    return Fname;
}

string Passenger::getLname() const{
    return Lname;
}

string Passenger::getPhoneNum() const{
    return phoneNum;
}

Seat Passenger::getSeat() const{
    return *seat;
}

unsigned int Passenger::getID() const{
    return ID;
}

void Passenger::DisplayInfo() const {
    cout << left << setw(20) <<Fname << setw(20) << Lname << setw(20) << phoneNum << setw(5) << seat->getRow() << setw(6) << seat->getColChar() << setw(7) << ID << "\n";
}
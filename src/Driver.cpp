#include "Driver.h"

Driver::Driver(){
    this->name = "Neznamy";
    this->employeeID = 0;
}

Driver::Driver(string name, int employeeID){
    this->name = name;
    this->employeeID = employeeID;
}

string Driver::getDetails() const {
    return "Vodic: " + this->name + " (ID: " + to_string(this->employeeID) + ")";
}

string Driver::getName() const { return this->name; }
int Driver::getID() const { return this->employeeID; }


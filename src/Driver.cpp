#include "Driver.h"
using namespace std;

Driver::Driver() {
    this->name       = "Neznamy";
    this->employeeID = 0;
}

Driver::Driver(string name, int employeeID) {
    this->name       = name;
    this->employeeID = employeeID;
}

string Driver::getDetails() const {
    return "Vodic: " + name + " (ID: " + to_string(employeeID) + ")";
}
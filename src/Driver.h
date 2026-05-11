#pragma once
#include<string>
using namespace std;

// Vodic priradeny k vozidlu. Pouziva sa ako kompozicia vo Vehicle.
class Driver {
private:
    string name;
    int employeeID;

public:
    Driver();
    Driver(string name, int employeeID);
    string getDetails() const;
    string getName() const;
    int getID() const;
};

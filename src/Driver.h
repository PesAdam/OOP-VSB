#pragma once
#include<string>

// Vodic priradeny k vozidlu. Pouziva sa ako kompozicia vo Vehicle.
class Driver {
private:
    std::string name;
    int employeeID;

public:
    Driver();
    Driver(std::string name, int employeeID);
    std::string getDetails() const;
    std::string getName() const;
    int getID() const;
};


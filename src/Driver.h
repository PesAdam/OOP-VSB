#pragma once
#include<string>

// [BOD 3] Driver sa pouziva ako kompozicia vo Vehicle (HAS-A vztah)
// Vozidlo MA vodica – Driver nie je rodic ani potomok, je to clen
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


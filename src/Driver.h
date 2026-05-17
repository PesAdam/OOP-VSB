#pragma once
#include <string>

// kompozicia – Driver je clen Vehicle (HAS-A)
class Driver {
    private:
        std::string name;
        int employeeID;
    public:
        Driver();
        Driver(std::string name, int employeeID);
        std::string getDetails() const;
};


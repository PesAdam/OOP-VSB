
#pragma once
#include "Vehicle.h"

class Tram : public Vehicle {
private:
    int pantographVoltage;   

public:
    Tram(int id, Driver d, Route r, int voltage);

    
    
    void drive() const override;
    int getPantographVoltage() const;
};

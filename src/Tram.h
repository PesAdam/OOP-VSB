#pragma once
#include "Vehicle.h"

// potomok Vehicle – rozsiruje data (pantographVoltage)
class Tram : public Vehicle {
    private:
        int pantographVoltage;
    public:
        Tram(int id, Driver d, Route r, int voltage);
        void drive() const override;   // zmena spravania
        int getPantographVoltage() const;
};

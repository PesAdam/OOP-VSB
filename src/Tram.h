#pragma once
#include "Vehicle.h"

// [BOD 6] Dedicna hierarchia – Tram je potomkom Vehicle
// [BOD 7] Rozsirenie dat (pantographVoltage) oproti predkovi
class Tram : public Vehicle {
private:
    int pantographVoltage;   // [BOD 7] Atribut specificky pre Tram

public:
    Tram(int id, Driver d, Route r, int voltage);

    // [BOD 7] Zmena spravania s neskoravou vazbou
    // [BOD 9] Polymorfne volanie cez Vehicle* v startSimulation()
    void drive() const override;
    int getPantographVoltage() const;
};


#pragma once
#include "Vehicle.h"

// ============================================================
// Trieda: Tram (Elektricka) - POTOMOK Vehicle
// ------------------------------------------------------------
// Konkretna implementacia vozidla typu elektricka.
// Dedicnostou ziskava vehicleID, driver, route a vsetky gettery z Vehicle.
// Rozsiruje predka o:
//   - pantographVoltage  (napatie pantografu v Voltoch)
//
// Implementuje cisto virtualnu metodu drive() z Vehicle.
// Vdaka tomu mozeme Tram* ulozit do Vehicle* a polymorfne volat drive().
// ============================================================
class Tram : public Vehicle {
private:
    int pantographVoltage;   // napatie elektrického pantografu (napr. 600V, 750V, 900V)

public:
    // Konstruktor - okrem ID, vodica a trasy prijima aj napatie pantografu
    Tram(int id, Driver d, Route r, int voltage);

    // Implementacia cisto virtualnej metody z Vehicle
    // override = oznacenie, ze prekryvame virtualnu metodu predka
    void drive() const override;

    // Getter pre napatie pantografu
    int getPantographVoltage() const;
};

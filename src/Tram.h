#pragma once
#include "Vehicle.h"

// [7] Tram je potomkom Vehicle – rozsiruje data aj metody
// Rozsirovanie dat:    pridava pantographVoltage (napatie pantografu)
// Zmena spravania:    implementuje drive() po svojom (neskorava vazba)
class Tram : public Vehicle {
    private:
        int pantographVoltage;  // elektricke napatie pantografu (600/750/900 V)

    public:
        Tram(int id, Driver d, Route r, int voltage);

        // [7] Override – Tram implementuje drive() inak ako Bus
        // Vola sa polymorfne cez Vehicle* v simulacii
        void drive() const override;
        int getPantographVoltage() const;
};

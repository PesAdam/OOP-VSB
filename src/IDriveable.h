#pragma once

// [BOD 8] Cisto abstraktna trieda – obsahuje iba pure virtual metody, ziadne data
// Funguje ako interface: kazda trieda ktora dedi od IDriveable MUSI implementovat drive()
// Neda sa priamo vytvorit objekt IDriveable
class IDriveable {
    public:
        virtual ~IDriveable() = default;
        virtual void drive() const = 0;
};

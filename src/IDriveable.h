#pragma once

// cisto abstraktna trieda (interface) – kazdy potomok musi implementovat drive()
class IDriveable {
    public:
        virtual ~IDriveable() = default;
        virtual void drive() const = 0;
};

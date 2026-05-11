#pragma once

class IDriveable {
    public:
        virtual ~IDriveable() = default;
        virtual void drive() const = 0;
};

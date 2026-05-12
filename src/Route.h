#pragma once
#include<string>

// [BOD 3] Route sa pouziva ako kompozicia vo Vehicle (HAS-A vztah)
// Vozidlo MA trasu – Route nie je rodic ani potomok, je to clen
class Route {
    private:
        std::string startStation;
        std::string endStation;

    public:
        Route();
        Route(std::string start, std::string end);
        std::string getRouteInfo() const;
        std::string getStart() const;
        std::string getEnd() const;
};


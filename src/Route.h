#pragma once
#include <string>

// kompozicia – Route je clen Vehicle (HAS-A)
class Route {
    private:
        std::string startStation;
        std::string endStation;
    public:
        Route();
        Route(std::string start, std::string end);
        std::string getRouteInfo() const;
};


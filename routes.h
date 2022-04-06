#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <math.h>
#include "airport.h"


class Routes {
    public:
        Routes(Airport dep, Airport dest);
        double calculateDistance(Airport dep, Airport dest);
        std::vector<double> cart_coordinates(double lat1, double long1);
        double getMagnitude(std::vector<double> loc);
        double getDistance(std::vector<double> loc1, std::vector<double> loc2);

    private:
        std::string departure;
        std::string destination;
        double distance;
};

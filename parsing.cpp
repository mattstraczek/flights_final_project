#pragma once
#include <iostream>
#include <fstream>
#include <unordered_map>
#include "airport.h"
#include "routes.h"

using namespace std;

class Parsing {
    public:
        std::vector<Airport> extractAirports(string fileName);
    private:
        unordered_map<string, Airport> 
}
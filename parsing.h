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
        std::vector<Routes> extractRoutes(string fileName);
    private:
        Airport createAirport(vector<string> data);
        Routes createRoutes(vector<string> data);

        std::vector<string> parseLine(string line);

        bool isInUS(vector<string> line);

        unordered_map<string, Airport> airport_map;
        unordered_map<Routes, int> route_map;
};
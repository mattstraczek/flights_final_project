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

        std::unordered_map<std::string, int> airport_map; //int = Airport index for now
        std::unordered_map<std::string, int> route_map; //route_map key == departure string + destination string
                                                        //eg. "ORDLAX"
};
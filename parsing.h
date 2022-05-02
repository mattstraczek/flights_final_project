#pragma once
#include <iostream>
#include <fstream>
#include <unordered_map>
#include "airport.h"
#include "routes.h"

using namespace std;

class Parsing {
    public:
        /**
         * default constructor for the Parsing class
         **/
        Parsing();

        /**
         * reads through the input file and creates an Airport object for each valid line of data, and populates the
         *   airport map with the airport ID as a key and the corresponding Airport object as the value
         * @param filename is a string representing the name of the file to read from
         **/
        void extractAirports(string fileName);

        /**
         * reads through the input file and creates a Routes object for each valid line of data, and populates the
         *   route map with the concatenated airport IDs as a key and 420 as the value, which shows that the route exists
         * @param filename is a string representing the name of the file to read from
         **/
        std::vector<Routes> extractRoutes(string fileName);

        /**
         * iterates through the airports in the airport map and writes the ID, latitude, and longitude of each to a file
         *   to assist in testing if the airport map is properly populated
         * @param filename is a string representing the name of the file to write to
         **/
        void writeAirports(string fileName);

        /**
         * returns the airport map so that it is accessible in graph.cpp and main.cpp
         * @return the airport map
         **/
        std::unordered_map<std::string, Airport> getAirportMap();

    private:
        Airport createAirport(vector<string> data);
        Routes createRoutes(vector<string> data);

        std::vector<string> parseLine(string line);

        bool isInUS(vector<string> line);

        std::unordered_map<std::string, Airport> airport_map; //int = Airport index for now
        std::unordered_map<std::string, int> route_map; //route_map key == departure string + destination string
                                                        //eg. "ORDLAX"
};

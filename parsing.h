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
         * returns the airport map so that it is accessible in graph.cpp and main.cpp
         * @return the airport map
         **/
        std::unordered_map<std::string, Airport> getAirportMap();
        /**
         * iterates through the airports in the airport map and writes the ID, latitude, and longitude of each to a file
         *   to assist in testing if the airport map is properly populated
         * @param filename is a string representing the name of the file to write to
         **/
        void writeAirports(string fileName);

    private:
        

        /**
         * takes a vector of strings from a line of data, and creates an Airport object with the airport ID, latitude, and
         *   longitude of the vector
         * @param data is a vector of strings created from the comma separated lines of airport data
         * @return an Airport with the ID, latitude, and longitude from data
         **/
        Airport createAirport(vector<string> data);

        /**
         * takes a vector of strings from a line of data, and creates a Routes object with the departure and destination
         *   data from the vector
         * @param data is a vector of strings created from the comma separated lines of route data
         * @return a Routes object with the departure and destination from data
         **/
        Routes createRoutes(vector<string> data);

        /**
         * takes a line of data from a file as string input and separates it into a vector of strings separated by the commas
         * @param line is a string of data from a file
         * @return a vector of the strings separated by the commas in lin
         **/
        std::vector<string> parseLine(string line);

        // unordered map that takes string IDs as keys and has the corresponding Airport as values
        std::unordered_map<std::string, Airport> airport_map; //int = Airport index for now

        // unordered map that takes a concatenation of IDs as keys and has ints as values (420 if the route exists)
        std::unordered_map<std::string, int> route_map; //route_map key == departure string + destination string
                                                        //eg. "ORDLAX"
};

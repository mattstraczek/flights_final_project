#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <math.h>
#include "airport.h"


class Routes {
    public:
        /**
         * default constructor of the Routes class, initializes a route with departure and destination as empty airports,
         *   and distance 0
         **/
        Routes();

        /**
         * constructor of the Routes class, initializes a route with departure dep, destination dest, and calculates the
         *   distance between them
         * @param dep is the departure Airport
         * @param dest is the destination Airport
         **/
        Routes(Airport dep, Airport dest);

        /**
         * calculates the distance between two Airports
	 * @param dep is the departure Airport
         * @param dest is the destination Airport
         * @return the distance between the airports
         **/
        double calculateDistance(Airport dep, Airport dest);

        /**
         * converts latitude and longitude coordinates to Cartesian coordinates
	 * @param lat1 is the latitude of an Airport
         * @param long1 is the longitude of an Airport
         * @return a vector of doubles representing the Cartesian coordinates
         **/
        std::vector<double> cart_coordinates(double lat1, double long1);

        /**
         * gets the magnitude of a Cartesian cooridinate
         * @param loc is a vector of doubles representing a Cartesian coordinate
         * @return the magnitude of the coordinate
         **/
        double getMagnitude(std::vector<double> loc);

        /**
         * returns the distance between two Cartesian coordinates
         * @param loc1 is the start Cartesian coordinate
         * @param loc2 is the end Cartesian coordinate
         * @return the distance between the two coordinates
         **/
        double getDistance(std::vector<double> loc1, std::vector<double> loc2);

        /**
         * returns the depature airport ID of this route
         * @return the depature airport ID of this route
         **/
        std::string getDeparture();

        /**
         * returns the destination airport ID of this route
         * @return the destination airport ID of this route
         **/
        std::string getDestination();

    private:
        Airport departure_; // the departure airport
        Airport destination_; // the destination airport
        double distance_; // the distance of this route
};






















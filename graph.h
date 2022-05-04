#pragma once
#include <vector>
#include <unordered_map>
#include <string>
#include "routes.h"
#include <list>
#include "cs225/PNG.h"
#include <iomanip>
#include <fstream>
#include <cmath>
#include <math.h>
#include <iterator>
#include <queue>
using namespace cs225;

class Graph{
    private:
      // struct for the adjacency list, stores the route destination, distance, and departure
      struct RouteEdge {
          RouteEdge(std::string airport_dest_, int distance_km_, std::string airport_dep_) {
            airport_dest = airport_dest_;
            distance_km = distance_km_;
//<<<<<<< HEAD
            // key value
            // previous airport 
//=======
            airport_dep = airport_dep_;
//>>>>>>> effcd421d004071f56135315b751bea6f42610e2
          }
          std::string airport_dest;
          int distance_km;
          std::string airport_dep;
        };
      struct compareInt {
        bool operator() (const std::pair<int, std::string> left, const std::pair<int, std::string> right) const {
          return left.first < right.first;
        }
      };

    public:
      /**
       * default constructor of the Graph class
       **/
      Graph();

      /**
       * constructor of the Graph class
       * @param airport_map is an unordered map with strings as keys and Airports as values, and maps the airport ID to a
       *   corresponding Airport object
       * @param route_list is a vector of Routes
       **/
      Graph(std::unordered_map<std::string, Airport> airport_map, std::vector<Routes> route_list);

      //Helper functions

      /**
       * writes a visual representation of the adjacency list to a file to help with testing and structure visualization
       **/
      void writeAdjListToFile(); // *******maybe move to private unless we want to run in main*******

      /**
       * returns the reduced airport map so it can be accessed in main.cpp
       * @return the reduced airport map, which is an unordered_map with strings as keys and Airports as values
       **/
      std::unordered_map<std::string, Airport> getReducedMap();

      /**
       * returns the reduced route list so it can be accessed in main.cpp
       * @return the reduced route list, which is a vector of Routes
       **/
      std::vector<Routes> getReducedRouteList();

      /**
       * returns the previous vector from Prim's algorithm so it can be accessed in main.cpp
       * @return the previous vector created during Prim's algorithm, which is a vector of strings
       **/
      std::vector<std::string> getPreviousVec();

      //Algorithms

      /**
       * performs Prim's algorithm on the adjacency list and returns a minimum spanning tree of the graph in the form of
       *   a vector of pairs of booleans and strings
       * @param start_id is a string representing the ID of the airport to start from
       * @return a vector of pairs of booleans and strings, where the boolean is true if the airport is in the MST and false
       *   otherwise, and the string is the airport ID
       **/
      std::vector<std::pair<bool, std::string>> primsMST(std::string start_id);

      /**
       * performs a breadth first search from a starting airport to an ending airport
       * @param start is the starting Airport for the algorithm
       * @param end is the ending Airport for the algorithm
       * @return a vector of strings representing the airport IDs in the order they are visited
       **/
      std::vector<std::string> BFS(Airport start, Airport end);

      /**
       * plots the MST output of Prim's algorithm onto a map of the world and saves it to a PNG file
       * @param start_id is a string representing the ID of the starting airport for Prim's algorithm
       * @param save_to is a string representing the name of the file to save the output to
       **/
      void printPrimsMST(std::string start_id, std::string save_to);

      //Helpers for geo-plotting algorithm

//      void writeReducedMatrixToFile(); *****delete?

      /**
       * Sets the canvas for the geographic map output from Mercator Projection
       **/
      void initgeoMap();

      /**
       * Creates a geoMap based on the minimum spanning tree of the world, MUST initialize initgeoMap() first
       * @param routes a vector of routes where the plot function will draw route path directly on to the map
       * @param hue change the hue of the color of the line
       **/
      void plotgeoMap(std::vector<Routes> routes, std::string save_to, int hue);

      /**
       * Creates a geoMap based on the minimum spanning tree of the world, MUST initialize initgeoMap() first
       * @param routes a vector of routes where the plot function will draw route path directly on to the map
       * @param hue is default to be 120;
       **/
      void plotgeoMap(std::vector<Routes> routes, std::string save_to);

      /**
       * converts a vector of string airport IDs to a vector of routes in the same order as the airports, allowing us to
       *   plot the output of BFS to a PNG
       * @param airports is a vector of strings representing airport IDs in the order they are visited in BFS
       * @return a vector of Routes created using the airport IDs from airports, keeping the BFS order
       **/
      std::vector<Routes> BFSRouteConvert(std::vector<std::string> airports);
      
      std::vector<Airport> getDestinations(int index); // ******add comments******

    private:
      /**
       * returns the adjacency list so it can be accessed in main.cpp
       * @return the adjacency list, which is a vector of lists of RouteEdges, with the first element of each list
       *   representing the departure of the routes, indexed by the unique airport index, and the following elements
       *   as the destinations
       **/
      std::vector<std::list<RouteEdge> >& getAdjList();

      /**
       * removes all Airports with no routes going to or from them from the airport map
       * @param route_list is a vector of Routes between Airports
       **/
      void reduceAirportMap(std::vector<Routes> &route_list);

      /**
       * removes all routes from the route list that include airports not in airport_map_reduced
       * @param route_list is a vector of Routes
       **/
      void reduceRouteList(std::vector<Routes> route_list);

      /**
       * A function that transforms latitude and longitude GIS information to the 2D canvas created
       * @param map pointer to a map that we want to print on 
       * @param lat_ latitude of the point of an airport or an increment of a path
       * @param long_ longitude of the point of an airport or an increement of a path
       * @return a pair of 2D cartesian coordinate of the mercator projection map
       **/
      std::pair<int, int> plotOnMap(PNG * map, double lat_, double long_);

      /**
       * Creates a path vector where it tells plotOnMap what latitude and longitude to plot for drawing a path
       * @param route One route class variable of the line/edge
       * @param n is an arbitrary step of drawing a path every n pixel steps
       * @return a vector of pairs where the pairs are all coordinates of the path taken by that route in latitude and longitude
       * */
      std::vector<std::pair<double, double>> drawLine(Routes route, int n);

      /**
       * Transforms latitude and longitude to 3D cartesian coordinate system of the planet Earth
       * @param lat_ the latitude of the point, N is +, S is -
       * @param long_ the longitude of the point, E is +, W is -
       * @return vector of double where there are 3 elements, in order, x,y,z coordinates
       **/
      std::vector<double> cart_coordinates(double lat_, double long_);

      /**
       * Transforms latitude and longitude to latitude and longitude coordinate system of the planet Earth
       * @param x coordinate in 3D space
       * @param y coordinate in 3D space
       * @param z coordinate in 3D space
       * @return a pair of latitude and longitude values
       **/
      std::pair<double, double> cart_to_lat_long(double x, double y, double z);

      /**
       * This is a function that projects the unit vector path towards the destination on to the surface of the Earth
       * @param curr is a reference to a vector of double where it takes in x,y,z cartesian coordinate of the current position
       **/
      void normalize(std::vector<double> & curr);

      /**
       * This is a function that returns the cross product between two 3 dimensional vectors
       * @param c1 first 3d vector
       * @param c2 second 3d vector
       * @return the 3d vector of the cross product
       **/
      std::vector<double> crossProd(std::vector<double> c1, std::vector<double> c2);

      /**
       * Calculates the distance between the two points on a cartesian coordinate along the curvature of the Earth
       * @param loc1
       * @param loc2 
       * @return returns the shortest direct distance along the Earth
       **/
      double getDistance(std::vector<double> loc1, std::vector<double> loc2);

      /**
       * Rehighlights surrounding dot to create thicker lines or thicker dot
       * @param x coordinate on the 2d map plane
       * @param y corrdinate of the 2d map plane
       * @param hue of the color
       **/
      void thickenDot(int x, int y, int hue);

      /**
       * Returns the magnitude of the 3 dimensional vector
       * @param loca a vector of the current location
       * @return the magnitude of the inputted vector
       **/
      double getMagnitude(std::vector<double> loc);

      /**
       * calculates the vector difference between point A and B
       * @param c1 is the vector of the first location
       * @param c2 is the vector of the second location
       * @return the vector of the difference between c1 and c2
       **/
      std::vector<double> findVec(std::vector<double> c1, std::vector<double> c2);

        //helper data structures
        std::unordered_map<std::string, Airport> airport_map; // maps string IDs to corresponding Airports
        std::unordered_map<std::string, Airport> airport_map_reduced; // airport map after all Airports with no routes have been removed
        std::vector<Routes> route_list_reduced; // vector of Routes after ones with Airports not in airport map have been removed
        //adjacency list
        std::vector<std::list<RouteEdge> > adj_list_reduced; // adjacency list, with the vector indexed by the unique airport indices, and the destinations as elements of the linked list

        //prims
        std::vector<std::string> previous; // intialize an array that holds the previous airport of the current airport, (aka where it came from) 
        std::vector<int> distance; // vector storing the distances for each vertex during Prim's

        PNG * geoMap; // PNG of a map for the Airports/Routes to be added to
};


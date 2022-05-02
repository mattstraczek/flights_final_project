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
      struct RouteEdge {
          RouteEdge(std::string airport_dest_, int distance_km_, std::string airport_dep_) {
            airport_dest = airport_dest_;
            distance_km = distance_km_;
            airport_dep = airport_dep_;
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
      Graph();
      Graph(std::unordered_map<std::string, Airport> airport_map, std::vector<Routes> route_list);

      //Helper functions
      void writeAdjListToFile();
      std::vector<std::list<RouteEdge> >& getAdjList();
      void reduceAirportMap(std::vector<Routes> &route_list);
      void reduceRouteList(std::vector<Routes> route_list);
      std::unordered_map<std::string, Airport> getReducedMap();
      std::vector<Routes> getReducedRouteList();
      std::vector<std::string> getPreviousVec();

      //Algorithms
      std::vector<std::pair<bool, std::string>> primsMST(std::string start_id);
      std::vector<std::string> BFS(Airport start, Airport end);

      void printPrimsMST(std::string start_id, std::string save_to);
      //Helpers for geo-plotting algorithm
      void writeReducedMatrixToFile();

      /**
       * Sets the canvas for the geographic map output from Mercator Projection
       * */
      void initgeoMap();

      /**
       * Creates a geoMap based on the minimum spanning tree of the world, MUST initialize initgeoMap() first
       * @param routes a vector of routes where the plot function will draw route path directly on to the map
       * */
      void plotgeoMap(std::vector<Routes> routes, std::string save_to);

      /**
       * A function that transforms latitude and longitude GIS information to the 2D canvas created
       * @param map pointer to a map that we want to print on 
       * @param lat_ latitude of the point of an airport or an increment of a path
       * @param long_ longitude of the point of an airport or an increement of a path
       * @return a pair of 2D cartesian coordinate of the mercator projection map
       * */
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
       * Returns the magnitude of the 3 dimensional vector
       * @param loca a vector of the current location
       * @return the magnitude of the inputted vector
       **/
      double getMagnitude(std::vector<double> loc);

      /**
       * Rehighlights surrounding dot to create thicker lines or thicker dot
       * @param x coordinate on the 2d map plane
       * @param y corrdinate of the 2d map plane
       * @param hue of the color
       **/
      void thickenDot(int x, int y, int hue);

      /**
       * calculates the vector difference between point A and B
       * @param c1 is the vector of the first location
       * @param c2 is the vector of the second location
       * @return the vector of the difference between c1 and c2
       **/
      std::vector<double> findVec(std::vector<double> c1, std::vector<double> c2);

      std::vector<Routes> BFSRouteConvert(std::vector<std::string> airports);

    private:
        //helper data structures
        std::unordered_map<std::string, Airport> airport_map;
        std::unordered_map<std::string, Airport> airport_map_reduced;
        std::vector<Routes> route_list_reduced;
        //adjacency list
        std::vector<std::list<RouteEdge> > adj_list_reduced;

        //prims
        std::vector<std::string> previous; // intialize an array that holds the previous airport of the current airport, (aka where it came from) 
        std::vector<int> distance;

        PNG * geoMap;
};


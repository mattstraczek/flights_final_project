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

      //Algorithms
      std::vector<bool> primsMST(std::string start_id);
      std::vector<std::string> BFS(Airport start, Airport end);


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
      void plotgeoMap(std::vector<Routes> routes);

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

      
      void normalize(std::vector<double> & curr);
      std::vector<double> crossProd(std::vector<double> c1, std::vector<double> c2);
      double getDistance(std::vector<double> loc1, std::vector<double> loc2);
      double getMagnitude(std::vector<double> loc);
      void thickenDot(int x, int y, int hue);
      std::vector<double> findVec(std::vector<double> c1, std::vector<double> c2);


      std::vector<std::string> BFS(Airport start, Airport end);
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


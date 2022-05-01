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
      void initgeoMap();
      void plotgeoMap(std::vector<Routes> routes);
      std::pair<int, int> plotOnMap(PNG * map, double lat_, double long_);
      std::vector<std::pair<double, double>> drawLine(Airport a1, Airport a2, int n);
      std::vector<double> cart_coordinates(double lat1, double long1);
      std::pair<double, double> cart_to_lat_long(double x, double y, double z);
      void normalize(std::vector<double> & curr);
      std::vector<double> crossProd(std::vector<double> c1, std::vector<double> c2);
      double getDistance(std::vector<double> loc1, std::vector<double> loc2);
      double getMagnitude(std::vector<double> loc);
      void thickenDot(int x, int y);
      std::vector<double> findVec(std::vector<double> c1, std::vector<double> c2);

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


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
          RouteEdge(std::string airport_dest_, int distance_km_) {
            airport_dest = airport_dest_;
            distance_km = distance_km_;
          }
          std::string airport_dest;
          int distance_km;
        };
        
    public:
      Graph();
      Graph(std::unordered_map<std::string, Airport> airport_map, std::vector<Routes> route_list);
      //Helper functions
      //void printRouteMatrix();
      //void printRouteMatrixLimited(int limit);
      void writeAdjListToFile();
      std::vector<std::list<RouteEdge> >& getAdjList();
      //Algorithms
      //std::vector<std::list<int> >& primsMST();
      //cs225::PNG * printRoutes();
      //std::vector<std::list<int> >& bfs_traversal(string start_airport, string end_airport);
      //testing reduced matrix
      void reduceAirportMap(std::vector<Routes> &route_list);
      void reduceAirportMatrix(std::vector<Routes> &route_list);
      std::unordered_map<std::string, Airport> getReducedMap();
      void writeReducedMatrixToFile();
      void initgeoMap();
      void plotgeoMap(std::vector<Routes> routes);
      std::pair<int, int> plotOnMap(PNG * map, double lat_, double long_);
      std::vector<std::string> BFS(Airport start, Airport end);
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
        std::vector<std::vector<int> > route_matrix;
        std::unordered_map<std::string, Airport> airport_map; //route_map key == departure string + destination string
                                                              //eg. "ORDLAX"
        //vector of routes
        std::vector<std::list<int> > route_mst;
        std::vector<std::list<int> > route_bfs;
        cs225::PNG route_img;

        //testing reduced matrix
        std::vector<std::vector<int> > route_matrix_reduced;
        std::unordered_map<std::string, Airport> airport_map_reduced;
        //testing reduced matrix

        //adjacency list
        std::vector<std::list<RouteEdge> > adj_list_reduced;

        PNG * geoMap;
};


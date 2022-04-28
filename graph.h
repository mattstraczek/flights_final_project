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
using namespace cs225;

class Graph{
    public:
      Graph();
      Graph(std::unordered_map<std::string, Airport> airport_map, std::vector<Routes> route_list);
      //Helper functions
      void printRouteMatrix();
      void printRouteMatrixLimited(int limit);
      void writeRouteMatrixToFile();
      std::vector<std::vector<int> >& getRouteMatrix();
      //Algorithms
      //std::vector<std::list<int> >& primsMST();
      //cs225::PNG * printRoutes();
      //std::vector<std::list<int> >& bfs_traversal(string start_airport, string end_airport);
      //testing reduced matrix
      void reduceAirportMap(std::vector<Routes> &route_list);
      void reduceAirportMatrix(std::vector<Routes> &route_list);
      void writeReducedMatrixToFile();
      void initgeoMap();
      void plotgeoMap();
      std::pair<int, int> plotOnMap(PNG * map, double lat_, double long_);
    private:
        std::vector<std::vector<int> > route_matrix;
        std::unordered_map<std::string, Airport> airport_map; //route_map key == departure string + destination string
                                                              //eg. "ORDLAX"
        std::vector<std::list<int> > route_mst;
        std::vector<std::list<int> > route_bfs;
        cs225::PNG route_img;

        //testing reduced matrix
        std::vector<std::vector<int> > route_matrix_reduced;
        std::unordered_map<std::string, Airport> airport_map_reduced;
        //testing reduced matrix
        PNG * geoMap;
};


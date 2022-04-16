#pragma once
#include <vector>
#include <unordered_map>
#include <string>
#include "routes.h"
#include <list>
#include "cs225/PNG.h"
#include <iomanip>

class Graph{
    public:
      Graph();
      Graph(std::unordered_map<std::string, Airport> airport_map, std::vector<Routes> route_list);
      void printRouteMatrix();
      void printRouteMatrixLimited(int limit);
      std::vector<std::vector<int> >& getRouteMatrix();
      //Algorithms
      std::vector<std::list<int> >& primsMST();
      cs225::PNG * printRoutes();
      std::vector<std::list<int> >& bfs_traversal(string start_airport, string end_airport);


    private:
        std::vector<std::vector<int> > route_matrix;
        std::unordered_map<std::string, Airport> airport_map; //route_map key == departure string + destination string
                                                              //eg. "ORDLAX"
        std::vector<std::list<int> > route_mst;
        std::vector<std::list<int> > route_bfs;
        cs225::PNG route_img;
};


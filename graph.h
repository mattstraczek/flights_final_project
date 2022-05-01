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
      void reduceRouteList(std::vector<Routes> route_list);
      void reduceAirportMatrix(std::vector<Routes> &route_list);
      std::unordered_map<std::string, Airport> getReducedMap();
      std::vector<Routes> getReducedRouteList();
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
        std::vector<std::vector<int> > route_matrix;
        std::unordered_map<std::string, Airport> airport_map; //route_map key == departure string + destination string
                                                              //eg. "ORDLAX"
        // std::vector<std::list<int> > route_mst;
        // std::vector<std::list<int> > route_bfs;
        cs225::PNG route_img;

        //testing reduced matrix
        std::vector<std::vector<int> > route_matrix_reduced;
        std::unordered_map<std::string, Airport> airport_map_reduced;
        std::vector<Routes> route_list_reduced;
        //testing reduced matrix

        //adjacency list
        std::vector<std::list<RouteEdge> > adj_list_reduced;

        PNG * geoMap;
};


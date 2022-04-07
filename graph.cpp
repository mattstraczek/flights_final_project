#include "graph.h"
#include "routes.h"
#include <unordered_map>
Graph::Graph(){
    
}
Graph::Graph(int airPortSize, std::unordered_map map_,std::vector<Routes> route_airports){
    airport_map = map_;
    route_matrix.resize(airPortSize);
    for(int i = 0; i < route_matrix.size(); i++){
        route_matrix[i].resize(airPortSize, -1);
    }
    for(int i = 0; i < route_airports.size(); i++){
        string start = route_airports[i].getStart(); //check routes class for functions
        string dest = route_airports[i].getDestination();
        int start_idx = airport_map[start];
        int dest_idx = airport_map[dest];
        route_matrix[start_idx][dest_idx] = route_airports[i].getDistance(); // write/check function exists

    }
}

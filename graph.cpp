#include "graph.h"
#include "routes.h"
#include <unordered_map>
Graph::Graph(){
    
}
Graph::Graph(int airPortSize, std::unordered_map<std::string, int> map_, std::vector<Routes> route_airports){
    route_map = map_;
    route_matrix.resize(airPortSize);
    for(unsigned long i = 0; i < route_matrix.size(); i++){
        route_matrix[i].resize(airPortSize, -1);
    }
    for(unsigned long i = 0; i < route_airports.size(); i++){
        std::string start = route_airports[i].getDeparture(); //check routes class for functions
        std::string dest = route_airports[i].getDestination();
        int start_idx = route_map[start];
        int dest_idx = route_map[dest];
        //route_matrix[start_idx][dest_idx] = route_airports[i].getDistance(); // write/check function exists 
                                                                               // FIX getDistance() PARAMETERS, maps have slightly changed in types, need to adjust

    }
}

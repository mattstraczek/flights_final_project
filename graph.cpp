#include "graph.h"

Graph::Graph() {
    
}
Graph::Graph(std::unordered_map<std::string, Airport> airport_map, std::vector<Routes> route_list) {
    int airPortSize = airport_map.size();
    this->airport_map = airport_map;
    route_matrix.resize(airPortSize);

    for(unsigned long i = 0; i < route_matrix.size(); i++) {
        route_matrix[i].resize(airPortSize, -1);
    }

    for(unsigned long i = 0; i < route_list.size(); i++) {
        std::string start = route_list[i].getDeparture(); //check routes class for functions
        std::string dest = route_list[i].getDestination();
        int start_idx = airport_map[start].getIndex();
        int dest_idx = airport_map[dest].getIndex();
        route_matrix[start_idx][dest_idx] = route_list[i].calculateDistance(airport_map[start], airport_map[dest]); // write/check function exists 
                                                                               // FIX getDistance() PARAMETERS, maps have slightly changed in types, need to adjust
    }
}
void Graph::printRouteMatrix() {
    std::vector<std::string> airport_ids;

    std::cout << std::setw(10) << "";
    for (const auto it : airport_map) {
        std::cout << std::setw(10) << std::left << it.first;
        airport_ids.push_back(it.first);
    }
    std::cout << std::endl;

    for (unsigned long i = 0; i < route_matrix.size(); i++) {
        std::cout << std::setw(10) << airport_ids[i];
        for (unsigned long j = 0; j < route_matrix[i].size(); j++) {
            std::cout << std::setw(10) << std::left << route_matrix[i][j];
        }
        std::cout << std::endl;
    }

}
void Graph::printRouteMatrixLimited(int limit) {
    std::vector<std::string> airport_ids;

    std::cout << std::setw(10) << "";
    int i = 0;
    for (const auto it : airport_map) {
        std::cout << std::setw(10) << std::left << it.first;
        airport_ids.push_back(it.first);
        i++;
        if (i >= limit) break;
    }
    std::cout << std::endl;

    for (int i = 0; i < limit; i++) {
        std::cout << std::setw(10) << airport_ids[i];
        for (int j = 0; j < limit; j++) {
            std::cout << std::setw(10) << std::left << route_matrix[i][j];
        }
        std::cout << std::endl;
    }
}
std::vector<std::vector<int> >& Graph::getRouteMatrix() {
    return route_matrix;
}
//Algorithms
// std::vector<std::list<int> >& Graph::primsMST() {

// }
// cs225::PNG * Graph::printRoutes() {

// }
// std::vector<std::list<int> >& Graph::bfs_traversal(string start_airport, string end_airport) {


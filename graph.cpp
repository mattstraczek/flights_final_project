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
    std::cout << "Route Matrix Size: " << route_matrix.size() << std::endl;
    std::vector<std::string> airport_ids(route_matrix.size());

    std::cout << std::setw(10) << "";
    for (const auto it : airport_map) {
        int index = it.second.getIndex();
        airport_ids[index] = it.first;
    }
    for (unsigned long i = 0; i < route_matrix.size(); i++) {
        std::cout << std::setw(10) << std::left << airport_ids[i];
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
void Graph::writeRouteMatrixToFile() {
    std::vector<std::string> airport_ids(route_matrix.size());

    std::ofstream route_matrix_stream;
    route_matrix_stream.open("Route_Matrix.txt");

    route_matrix_stream << std::setw(10) << "";
    for (const auto it : airport_map) {
        int index = it.second.getIndex();
        airport_ids[index] = it.first;
    }
    for (unsigned long i = 0; i < route_matrix.size(); i++) {
        route_matrix_stream << std::setw(10) << std::left << airport_ids[i];
    }
    route_matrix_stream << std::endl;

    for (unsigned long i = 0; i < route_matrix.size(); i++) {
        route_matrix_stream << std::setw(10) << airport_ids[i];
        for (unsigned long j = 0; j < route_matrix[i].size(); j++) {
            route_matrix_stream << std::setw(10) << std::left << route_matrix[i][j];
        }
        route_matrix_stream << std::endl;
    }

}
void Graph::printRouteMatrixLimited(int limit) {
    std::cout << "Route Matrix Size: " << route_matrix.size() << std::endl;
    std::vector<std::string> airport_ids(route_matrix.size());

    std::cout << std::setw(10) << "";
    int i = 0;
    for (const auto it : airport_map) {
        int index = it.second.getIndex();
        airport_ids[index] = it.first;
        // i++;
        // if (i >= limit) break;
    }
    for (int i = 0; i < limit; i++) {
        std::cout << std::setw(10) << std::left << airport_ids[i];
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
   // read from adjacency matrix 
    //  in route_matrix each cell acts as an edge in the graph
    //  where the edges weight is determined by its geographical distance between airports (vertices)
    
    // set an arbitrary airport within route_matrix as the start matrix

    // create a distance vector to keep track of distance from previous airport
    // create a predecessor vector to keep track of previous airport
    // to initialize set all airport (vertices)... 
    //  -> distance[i] = infinity
    //  -> pred[i] = null;
    // For Start:
    //      -> dist[start_index] = 0
    //      -> pred[start_index] = null
    // can maybe avoid using multiple vectors if each element within the priority queue holds distance and predecessor value  

    // create a priority queue, where each element in the queue holds two values: distance and predecessor 
    // -> distance describes the geographical distance between airport and neighboring airport 
    // -> predecessor describes the previous airport
    // the priority queue is sorted by the distance characteristic of each element in the queue
    // Offers insight how to create a min-heap using C++'s STL of priority queues  https://www.geeksforgeeks.org/implement-min-heap-using-stl/

    // LOOP thru until the queue is empty
    //
    // pop the minimum element from the heap, meaning the airport with the minimum distance  
    // at first the starting airport is popped because 0 <<< infinity
    //
    // add the popped element, aiport,   to the MST vector 
    // for all adjacent (neighboring) airports of popped airport update their distances using the data from the adjacency matrix
    // update their distance in the priority queue, so the airport with the smallest distance is placed at the top of the 
    // priority queue
    // Go back to top of loop
    //


//}
// cs225::PNG * Graph::printRoutes() {

// }
// std::vector<std::list<int> >& Graph::bfs_traversal(string start_airport, string end_airport) {

//testing reduced matrix
void Graph::reduceAirportMap(std::vector<Routes>& route_list) {
    std::unordered_map<std::string, int> route_departures;
    std::unordered_map<std::string, int> route_destinations;
    //Populate route maps with their corresponding airports
    for (auto route : route_list) {
        if (route_departures.find(route.getDeparture()) == route_departures.end()) {
            route_departures[route.getDeparture()] = 1;
        }
        if (route_destinations.find(route.getDestination()) == route_destinations.end()) {
            route_destinations[route.getDestination()] = 1;
        }
    }
    //Filter out airports that only appear in the routes into the new reduced airport_map
    for (auto airport : airport_map) {
        if (route_departures.find(airport.second.getID()) != route_departures.end() || route_destinations.find(airport.second.getID()) != route_destinations.end()) {
            Airport temp = airport.second;
            temp.setIndex(airport_map_reduced.size());
            airport_map_reduced[airport.second.getID()] = temp;
        }
    }
    std::cout << "Reduced airport_map size: " << airport_map_reduced.size() << std::endl;
}
void Graph::reduceAirportMatrix(std::vector<Routes>& route_list) {
    int airPortSize = airport_map_reduced.size();
    route_matrix_reduced.resize(airPortSize);

    for(unsigned long i = 0; i < route_matrix_reduced.size(); i++) {
        route_matrix_reduced[i].resize(airPortSize, -1);
    }

    for(unsigned long i = 0; i < route_list.size(); i++) {
        std::string start = route_list[i].getDeparture(); //check routes class for functions
        std::string dest = route_list[i].getDestination();
        int start_idx = airport_map_reduced[start].getIndex();
        int dest_idx = airport_map_reduced[dest].getIndex();
        route_matrix_reduced[start_idx][dest_idx] = route_list[i].calculateDistance(airport_map_reduced[start], airport_map_reduced[dest]); // write/check function exists 
                                                                               // FIX getDistance() PARAMETERS, maps have slightly changed in types, need to adjust
    }
}
void Graph::writeReducedMatrixToFile() {
    std::vector<std::string> airport_ids(route_matrix_reduced.size());

    std::ofstream route_matrix_stream;
    route_matrix_stream.open("Reduced_Matrix.txt");

    route_matrix_stream << std::setw(10) << "";
    for (const auto it : airport_map_reduced) {
        int index = it.second.getIndex();
        airport_ids[index] = it.first;
    }
    for (unsigned long i = 0; i < route_matrix_reduced.size(); i++) {
        route_matrix_stream << std::setw(10) << std::left << airport_ids[i];
    }
    route_matrix_stream << std::endl;

    for (unsigned long i = 0; i < route_matrix_reduced.size(); i++) {
        route_matrix_stream << std::setw(10) << airport_ids[i];
        for (unsigned long j = 0; j < route_matrix_reduced[i].size(); j++) {
            route_matrix_stream << std::setw(10) << std::left << route_matrix_reduced[i][j];
        }
        route_matrix_stream << std::endl;
    }

}

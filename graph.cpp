#include "graph.h"
using namespace cs225;


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

void Graph::initgeoMap() {
    geoMap = new PNG();
    geoMap->readFromFile("mercator_map.png");
    geoMap->scale(3);
}
//creates a geoMap based on the minimum spanning tree of the world
void Graph::plotgeoMap() {
    //create a new canvas by reading from existing map base
    std::cout << "the size of the map is in order of width height, " << geoMap->width() << ", " << geoMap->height() << std::endl;
    //plot on Map CHICAGO
    // std::pair<int, int> map_coordinates1 = plotOnMap(geoMap, 41.8781,-87.6298);

    //plot on Map YOKOHAMA
    std::pair<int, int> map_coordinates1 = plotOnMap(geoMap, -33.8688, 151.2093);
    // std::pair<int, int> map_coordinates1 = plotOnMap(geoMap, 0, -15);
    // std::pair<int, int> map_coordinates2 = plotOnMap(geoMap, 15, 0);
    // std::pair<int, int> map_coordinates3 = plotOnMap(geoMap, 30, 0);
    // std::pair<int, int> map_coordinates4 = plotOnMap(geoMap, 45, 0);
    // std::pair<int, int> map_coordinates5 = plotOnMap(geoMap, 75, 0);

    // std::cout << map_coordinates1.first << ", " << map_coordinates1.second << std::endl;
    // HSLAPixel& curr = geoMap->getPixel(map_coordinates1.first, map_coordinates1.second);
    // int temp_x = map_coordinates1.first;
    // int temp_y = map_coordinates1.second;
    // for(size_t i = temp_y; i < geoMap->height(); i++) {
    //     HSLAPixel& curr = geoMap->getPixel(temp_x, i);
    //     curr.h = 0;
    //     curr.s = 1;
    //     curr.l = 0.5;
    // }
    // std::cout << map_coordinates2.first << ", " << map_coordinates2.second << std::endl;

    // temp_x = map_coordinates2.first;
    // temp_y = map_coordinates2.second;
    // for(size_t i = temp_x; i < geoMap->width(); i++) {
    //     HSLAPixel& curr = geoMap->getPixel(i, temp_y);
    //     curr.h = 0;
    //     curr.s = 1;
    //     curr.l = 0.5;
    // }
    // std::cout << map_coordinates3.first << ", " << map_coordinates3.second << std::endl;

    // temp_x = map_coordinates3.first;
    // temp_y = map_coordinates3.second;
    // for(size_t i = temp_x; i < geoMap->width(); i++) {
    //     HSLAPixel& curr = geoMap->getPixel(i, temp_y);
    //     curr.h = 0;
    //     curr.s = 1;
    //     curr.l = 0.5;
    // }

    // temp_x = map_coordinates4.first;
    // temp_y = map_coordinates4.second;
    // for(size_t i = temp_x; i < geoMap->width(); i++) {
    //     HSLAPixel& curr = geoMap->getPixel(i, temp_y);
    //     curr.h = 0;
    //     curr.s = 1;
    //     curr.l = 0.5;
    // }

    // temp_x = map_coordinates5.first;
    // temp_y = map_coordinates5.second;
    // for(size_t i = temp_x; i < geoMap->width(); i++) {
    //     HSLAPixel& curr = geoMap->getPixel(i, temp_y);
    //     curr.h = 0;
    //     curr.s = 1;
    //     curr.l = 0.5;
    // }

    std::unordered_map<std::string, Airport>::iterator it;

    for(it = airport_map.begin(); it != airport_map.end(); it++) {
        Airport current = it->second;
        if((it->first) == "ORD") {
            std::pair<int, int> map_coordinate = plotOnMap(geoMap, current.getLatitude(), current.getLongitude());
            HSLAPixel& curr = geoMap->getPixel(map_coordinate.first, map_coordinate.second);
            curr.h = 120;
            curr.s = 1;
            curr.l = 0.5;
        } else {
            std::pair<int, int> map_coordinate = plotOnMap(geoMap, current.getLatitude(), current.getLongitude());
            HSLAPixel& curr = geoMap->getPixel(map_coordinate.first, map_coordinate.second);
            curr.h = 0;
            curr.s = 1;
            curr.l = 0.5;
        }
        
        
    }

    //output the image to the final file
    geoMap->writeToFile("geographic_map.png");
    delete geoMap;   
}

std::pair<int, int> Graph::plotOnMap(PNG * map, double lat_, double long_) {
    double long_step = (map->width() -28)/360.0; //pixels per degrees
    double lat_step = map->height()/180.0; //pixels per degrees

    std::cout << lat_step << ", " << long_step << std::endl;
    double origin_x = map->width()/2.0;
    double origin_y = map->height()/2.0;

    int x = origin_x + (long_step * long_);
    double theta = lat_*3.14159265/180;
    double val = sqrt(sqrt(1/cos(theta)));
    std::cout << "the continuous scale factor is: " << 1/cos(theta) << std::endl;
    int y = (origin_y - (long_step * lat_));
    std::cout << "y before scaling is " << y << std::endl;

    y = (origin_y - (long_step * lat_)*pow(val, 1.28));
    std::cout << "y after scaling is " << y << std::endl;


    std::pair<int, int> coord(x,y);

    return coord;
}

// //draw line between two points on a 2D cartesian coordinate map
// void drawLine(int x1, int y1, int x2, int y2) {

// }

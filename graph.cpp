#include "graph.h"
using namespace cs225;


Graph::Graph() {
    
}
Graph::Graph(std::unordered_map<std::string, Airport> airport_map, std::vector<Routes> route_list) {
    // int airPortSize = airport_map.size();
    // this->airport_map = airport_map;
    // route_matrix.resize(airPortSize);

    // for(unsigned long i = 0; i < route_matrix.size(); i++) {
    //     route_matrix[i].resize(airPortSize, -1);
    // }

    // for(unsigned long i = 0; i < route_list.size(); i++) {
    //     std::string start = route_list[i].getDeparture(); //check routes class for functions
    //     std::string dest = route_list[i].getDestination();
    //     int start_idx = airport_map[start].getIndex();
    //     int dest_idx = airport_map[dest].getIndex();
    //     route_matrix[start_idx][dest_idx] = route_list[i].calculateDistance(airport_map[start], airport_map[dest]); // write/check function exists 
    //                                                                            // FIX getDistance() PARAMETERS, maps have slightly changed in types, need to adjust
    // }
    this->airport_map = airport_map;
    reduceAirportMap(route_list);
    size_t airPortSize = airport_map_reduced.size();
    for (size_t i = 0; i < airPortSize; i++) {
        adj_list_reduced.push_back(std::list<RouteEdge>());
    }
    //route_list_reduced.resize(airPortSize);

    for(unsigned long i = 0; i < route_list.size(); i++) {
        std::string start = route_list[i].getDeparture(); //check routes class for functions
        std::string dest = route_list[i].getDestination();
        int start_idx = airport_map_reduced[start].getIndex();
        //int dest_idx = airport_map[dest].getIndex();
        double distance = route_list[i].calculateDistance(airport_map_reduced[start], airport_map_reduced[dest]);
        RouteEdge temp_route_node(dest, distance);
        adj_list_reduced[start_idx].insert(adj_list_reduced[start_idx].begin(), temp_route_node); 
    }
}
// void Graph::printRouteMatrix() {
//     std::cout << "Route Matrix Size: " << route_matrix.size() << std::endl;
//     std::vector<std::string> airport_ids(route_matrix.size());

//     std::cout << std::setw(10) << "";
//     for (const auto it : airport_map) {
//         int index = it.second.getIndex();
//         airport_ids[index] = it.first;
//     }
//     for (unsigned long i = 0; i < route_matrix.size(); i++) {
//         std::cout << std::setw(10) << std::left << airport_ids[i];
//     }
//     std::cout << std::endl;

//     for (unsigned long i = 0; i < route_matrix.size(); i++) {
//         std::cout << std::setw(10) << airport_ids[i];
//         for (unsigned long j = 0; j < route_matrix[i].size(); j++) {
//             std::cout << std::setw(10) << std::left << route_matrix[i][j];
//         }
//         std::cout << std::endl;
//     }

// }
void Graph::writeAdjListToFile() {
    std::vector<std::string> airport_ids(adj_list_reduced.size());

    std::ofstream route_matrix_stream;
    route_matrix_stream.open("Adj_list.txt");

    //route_matrix_stream << std::setw(10) << "";
    for (const auto it : airport_map_reduced) {
        int index = it.second.getIndex();
        airport_ids[index] = it.first;
    }
    // for (unsigned long i = 0; i < adj_list_reduced.size(); i++) {
    //     route_matrix_stream << std::setw(10) << std::left << airport_ids[i];
    // }
    //route_matrix_stream << std::endl;

    for (unsigned long i = 0; i < adj_list_reduced.size(); i++) {
        route_matrix_stream << std::setw(7) << std::left << airport_ids[i];
        for (auto route : adj_list_reduced[i]) {
            route_matrix_stream << std::setw(7) << std::left << "-->" << "[" << route.airport_dest << ", " << route.distance_km << "]";
        }
        route_matrix_stream << std::endl;
    }

}
// void Graph::printRouteMatrixLimited(int limit) {
//     std::cout << "Route Matrix Size: " << route_matrix.size() << std::endl;
//     std::vector<std::string> airport_ids(route_matrix.size());

//     std::cout << std::setw(10) << "";
//     int i = 0;
//     for (const auto it : airport_map) {
//         int index = it.second.getIndex();
//         airport_ids[index] = it.first;
//         // i++;
//         // if (i >= limit) break;
//     }
//     for (int i = 0; i < limit; i++) {
//         std::cout << std::setw(10) << std::left << airport_ids[i];
//     }
//     std::cout << std::endl;

//     for (int i = 0; i < limit; i++) {
//         std::cout << std::setw(10) << airport_ids[i];
//         for (int j = 0; j < limit; j++) {
//             std::cout << std::setw(10) << std::left << route_matrix[i][j];
//         }
//         std::cout << std::endl;
//     }
// }
std::vector<std::list<Graph::RouteEdge> >& Graph::getAdjList() {
    return adj_list_reduced;
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
/*
std::vector<std::list<int> >& Graph::primsMST() {
    //std::vector<std::list<RouteEdge> > adj_list_reduced;
    int sizeOfGraph =  adj_list_reduced.size(); // number of vertices in the graph
    RouteEdge previous[sizeOfGraph] // intialize an array that holds the previous airport of the current airport, (aka where it came from) 
    int key[sizeOfGraph]; // intialie an array that holds the key value for each vertex in the graph

    for(int i = 0; i < sizeOfGraph; i++){
        previous[i] = NULL;
        key[i] = +inf;
    }
    //figure out start airport**********
    key[start_index] = 0;
    //inlcude an index, with each key value
    // so know where to find it in the adjacency list
    
    priority_queue <int, vector<pair<int, int>>, greater<pair<int, int>>> min_heap;
    //builds heap
    for(int i = 0; i < sizeOfGraph; i++){
        min_heap.push(std::make_pair(key[i],i));
    }
    //initialize return vector T

    while(!min.heap.empty()){
        std::pair<int, int> smallest_route = min_heap.top(); //remove vertix from the graph with the smallest distance between airports
        min_heap.pop();
        //add to return vector T
        //find neighbors of currently removed vertex
        //list of neighboring edges of smallest element
        // adj_list_reduced[smallest_route.first];
        std::list<RouteEdge>iterator it;
        for(it = adj_list_reduced[smallest_route.first].begin(); it != adj_list_reduced[smallest_route.first].end(); it++){
            if (cost(*it,adj_list_reduced[smallest_route.first]){
                d[]
            }
        }
        
    }
*/
    // }
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
// void Graph::reduceAirportMatrix(std::vector<Routes>& route_list) {
//     int airPortSize = airport_map_reduced.size();
//     route_matrix_reduced.resize(airPortSize);

//     for(unsigned long i = 0; i < route_matrix_reduced.size(); i++) {
//         route_matrix_reduced[i].resize(airPortSize, -1);
//     }

//     for(unsigned long i = 0; i < route_list.size(); i++) {
//         std::string start = route_list[i].getDeparture(); //check routes class for functions
//         std::string dest = route_list[i].getDestination();
//         int start_idx = airport_map_reduced[start].getIndex();
//         int dest_idx = airport_map_reduced[dest].getIndex();
//         route_matrix_reduced[start_idx][dest_idx] = route_list[i].calculateDistance(airport_map_reduced[start], airport_map_reduced[dest]); // write/check function exists 
//                                                                                // FIX getDistance() PARAMETERS, maps have slightly changed in types, need to adjust
//     }
// }
// void Graph::writeReducedMatrixToFile() {
//     std::vector<std::string> airport_ids(route_matrix_reduced.size());

//     std::ofstream route_matrix_stream;
//     route_matrix_stream.open("Reduced_Matrix.txt");

//     route_matrix_stream << std::setw(10) << "";
//     for (const auto it : airport_map_reduced) {
//         int index = it.second.getIndex();
//         airport_ids[index] = it.first;
//     }
//     for (unsigned long i = 0; i < route_matrix_reduced.size(); i++) {
//         route_matrix_stream << std::setw(10) << std::left << airport_ids[i];
//     }
//     route_matrix_stream << std::endl;

//     for (unsigned long i = 0; i < route_matrix_reduced.size(); i++) {
//         route_matrix_stream << std::setw(10) << airport_ids[i];
//         for (unsigned long j = 0; j < route_matrix_reduced[i].size(); j++) {
//             route_matrix_stream << std::setw(10) << std::left << route_matrix_reduced[i][j];
//         }
//         route_matrix_stream << std::endl;
//     }

// }

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

    //plot paths of routes
    std::vector<std::pair<double, double>> path = drawLine(10);
    for(size_t i = 0; i < path.size(); i++) {
        std::pair<int, int> path_coordinate = plotOnMap(geoMap, path[i].first, path[i].second);
        // std::cout << path_coordinate.first << ", " << path_coordinate.second << std::endl;
        // for (int i = path_coordinate.first-1; i < 2; i++) {
        //     for (int j = path_coordinate.second-1; j < 2; j++) {
        //         HSLAPixel& curr = geoMap->getPixel(i,j);
        //         curr.h = 120;
        //         curr.s = 1;
        //         curr.l = 0.5;
        //     }
        // }
        HSLAPixel& curr = geoMap->getPixel(path_coordinate.first, path_coordinate.second);
        curr.h = 120;
        curr.s = 1;
        curr.l = 0.5;
    }


    //output the image to the final file
    geoMap->writeToFile("geographic_map.png");
    delete geoMap;   
}

void Graph::thickenDot(int x, int y) {
    for (int i = x-1; i < 2; i++) {
        for (int  j = y-1; j < 2; j++) {
            HSLAPixel& curr = geoMap->getPixel(i,j);
            curr.h = 120;
            curr.s = 1;
            curr.l = 0.5;
        }
    }
}
std::pair<int, int> Graph::plotOnMap(PNG * map, double lat_, double long_) {
    double long_step = (map->width() -28)/360.0; //pixels per degrees
    double lat_step = map->height()/180.0; //pixels per degrees

    // std::cout << lat_step << ", " << long_step << std::endl;
    double origin_x = map->width()/2.0;
    double origin_y = map->height()/2.0;

    int x = origin_x + (long_step * long_);
    double theta = lat_*3.14159265/180;
    double val = sqrt(sqrt(1/cos(theta)));
    // std::cout << "the continuous scale factor is: " << 1/cos(theta) << std::endl;
    int y = (origin_y - (long_step * lat_));
    // std::cout << "y before scaling is " << y << std::endl;

    y = (origin_y - (long_step * lat_)*pow(val, 1.28));
    // std::cout << "y after scaling is " << y << std::endl;


    std::pair<int, int> coord(x,y);

    return coord;
}

//draw line between two points on a 2D cartesian coordinate map
//steps n is by default 10
std::vector<std::pair<double, double>> Graph::drawLine(int n) {
    Airport a1;
    Airport a2;

    // if(airport_map_reduced.find(route.getDeparture()) != airport_map_reduced.end()) {
    //     a1 = airport_map_reduced.find(route.getDeparture())->second;
    // }
    // if(airport_map_reduced.find(route.getDestination()) != airport_map_reduced.end()) {
    //     a2 = airport_map_reduced.find(route.getDestination())->second;
    // }


    //========EXAMPLE==========
    a1.setLatitude(41.8781);
    a1.setLongitude(-87.6298);

    a2.setLatitude(29.7604);
    a2.setLongitude(-95.3698);
    //*************************
    std::vector<double> threeDCoord1 = cart_coordinates(a1.getLatitude(), a1.getLongitude());
    std::vector<double> threeDCoord2 = cart_coordinates(a2.getLatitude(), a2.getLongitude());

    std::vector<double> unit_product;

    std::vector<std::pair<double, double>> recorded_path;
    std::vector<double> current = threeDCoord1;

    std::cout << "========================line427========================" << std::endl;
    bool not_arrived = true;
    //set i boundary by calculating the distance between to come up with optimal sample size
    
    for (int i = 0; i < 8000; i++) {
        unit_product = findVec(current, threeDCoord2);
        current[0] += unit_product[0] * n;
        current[1] += unit_product[1] * n;
        current[2] += unit_product[2] * n;
        normalize(current);
        if(getDistance(current, threeDCoord2) < 10) {
            std::cout << "<--l---arrived!----------P" << std::endl;
            break;
        }
        std::cout << "========================437========================" << std::endl;

        std::cout << "the path lat long are " << cart_to_lat_long(current[0], current[1], current[2]).first<< ", " << cart_to_lat_long(current[0], current[1], current[2]).second<< std::endl;
        recorded_path.push_back(cart_to_lat_long(current[0], current[1], current[2]));
    }
    return recorded_path;
}

double Graph::getMagnitude(std::vector<double> loc) {
    double mag = sqrt(loc[0]*loc[0] + loc[1]*loc[1] + loc[2]*loc[2]);
    return mag;
}

double Graph::getDistance(std::vector<double> loc1, std::vector<double> loc2) {
    //get dot product first
    const double pi = 2 * acos(0.0);
    
    const double re = 6378.1; //in kilo-meters
    double dotProduct = loc1[0]*loc2[0] + loc1[1]*loc2[1] + loc1[2]*loc2[2];
    double magProduct = getMagnitude(loc1) * getMagnitude(loc2);
    
    //acos() here returns the radian. The radian between two cities 
    //and radius of the earth gives curve length assuming earth is a uniform sphere
    return (acos(dotProduct/magProduct))*re;
}

std::vector<double> Graph::cart_coordinates(double lat1, double long1) {
    std::vector<double> coordinates;
    double pi = 2 * acos(0.0);
    //calculates the 3D cartesian coordinates of the lat long
    // const double re = 6378.1; //in kilo-meters
    const double re = 6378.1;
    double phi = lat1*pi/180;
    double lda = long1*pi/180;
    double x = re * cos(phi) * cos(lda);
    double y = re * cos(phi) * sin(lda);
    double z = re * sin(phi);
    
    coordinates.push_back(x);
    coordinates.push_back(y);
    coordinates.push_back(z);
    
    return coordinates;
}

std::pair<double, double> Graph::cart_to_lat_long(double x, double y, double z) {
    std::pair<double, double> lat_long;
    const double re = 6378.1;
    double pi = 2 * acos(0.0);

    double phi = asin(z / re);

    // std::cout << "testing number ========> " << y - re * cos(phi) << std::endl;
    double neg = 1.0;
    if(y < 0) {
        neg = -1.0;
    }
    double lda = neg*acos((x/(re * cos(phi))));
    double lat_ = phi * 180 / pi;
    double long_ = lda * 180 / pi;
    std::cout << std::endl;
    std::cout << "===================================================" << std::endl;
    std::cout << "phi = " << phi << std::endl;
    std::cout << "lda = " << lda << std::endl;
    std::cout << "x,y,z" << x << ", " << y << ", " << z << std::endl;
    std::cout << "===================================================" << std::endl;
    // std::cout << std::endl;
    // std::cout << "printing lat_ " << lat_ <<std::endl;
    // std::cout << "printing long_ " << long_ <<std::endl;
    lat_long.first = lat_;
    lat_long.second = long_;
    // std::cout << "inside cart_to_lat_long" << std::endl;
    // std::cout << lat_ << ", " << long_ << std::endl;

    return lat_long;
}


void Graph::normalize(std::vector<double> & curr) {
    double mag = sqrt(curr[0]*curr[0] + curr[1]*curr[1] + curr[2]*curr[2]);
    curr[0] /= mag;
    curr[1] /= mag;
    curr[2] /= mag;
    double n = 6378.1 / sqrt(curr[0]*curr[0] + curr[1]*curr[1] + curr[2]*curr[2]);

    curr[0] *= n;
    curr[1] *= n;
    curr[2] *= n;

    return;
}

std::vector<double> Graph::crossProd(std::vector<double> c1, std::vector<double> c2) {
    std::vector<double> product;
    double ax = c1[0]/6378.1;
    double bx = c2[0]/6378.1;
    double ay = c1[1]/6378.1;
    double by = c2[1]/6378.1;
    double az = c1[2]/6378.1;
    double bz = c2[2]/6378.1;
    //for i componenet
    product.push_back(ay*bz - az*by);
    product.push_back(-(ax*bz - az*bx));
    product.push_back(ax*by - ay*bx);
    
    return product;
}


std::vector<double> Graph::findVec(std::vector<double> c1, std::vector<double> c2) {
    std::vector<double> direction;
    double ax = c1[0];
    double bx = c2[0];
    double ay = c1[1];
    double by = c2[1];
    double az = c1[2];
    double bz = c2[2];

    direction.push_back((bx-ax)/6378.1);
    direction.push_back((by-ay)/6378.1);
    direction.push_back((bz-az)/6378.1);

    return direction;
}


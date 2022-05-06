#include "graph.h"

using namespace cs225;

Graph::Graph() {
    
}

Graph::Graph(std::unordered_map<std::string, Airport> airport_map, std::vector<Routes> route_list) {
    this->airport_map = airport_map;
    // remove all unused airports and routes from the input
    reduceAirportMap(route_list);
    reduceRouteList(route_list);
    route_list = route_list_reduced;
    size_t airPortSize = airport_map_reduced.size();
    // initialize a vector of empty lists
    for (size_t i = 0; i < airPortSize; i++) {
        adj_list_reduced.push_back(std::list<RouteEdge>());
    }

    for(unsigned long i = 0; i < route_list.size(); i++) {
        std::string start = route_list[i].getDeparture(); //check routes class for functions
        std::string dest = route_list[i].getDestination();
        int start_idx = airport_map_reduced[start].getIndex();
        double distance = route_list[i].calculateDistance(airport_map_reduced[start], airport_map_reduced[dest]);
        // create a RouteEdge with the destination, distance, and departure from the current route and add to list
        RouteEdge temp_route_node(dest, distance, start);
        adj_list_reduced[start_idx].insert(adj_list_reduced[start_idx].begin(), temp_route_node); 
    }
    // iterate through the airports in the reduced airport map
    for (const auto it : airport_map_reduced) {
        double distance = 0;
        int index = it.second.getIndex();
        std::string start = it.first;
        RouteEdge temp_route_node(start, distance, start);
        // add a RouteEdge from departure to departurn to the beginning of the list at its corresponding index
        adj_list_reduced[index].insert(adj_list_reduced[index].begin(), temp_route_node); 
    }
}

void Graph::writeAdjListToFile() {
    std::vector<std::string> airport_ids(adj_list_reduced.size());

    std::ofstream route_matrix_stream;
    route_matrix_stream.open("Adj_list.txt");

    // add each airport ID to its corresponding index in the airport_ids vector
    for (const auto it : airport_map_reduced) {
        int index = it.second.getIndex();
        airport_ids[index] = it.first;
    }

    // write the adjacency list to a file in a format that makes it easy to visualize
    for (unsigned long i = 0; i < adj_list_reduced.size(); i++) {
        route_matrix_stream << std::setw(7) << std::left << airport_ids[i];
        for (auto route : adj_list_reduced[i]) {
            route_matrix_stream << std::setw(7) << std::left << "-->" << "[" << route.airport_dest << ", " << route.distance_km << ", " << route.airport_dep << "]";
        }
        route_matrix_stream << std::endl;
    }

}

std::vector<std::list<Graph::RouteEdge> >& Graph::getAdjList() {
    return adj_list_reduced;
}

std::vector<std::pair<bool, std::string>> Graph::primsMST(std::string start_id) {
    previous.resize(0);
    distance.resize(0);
    size_t sizeOfGraph =  adj_list_reduced.size(); // number of vertices in the graph
    previous.resize(0);
    distance.resize(0);
    previous.resize(sizeOfGraph, ""); // intialize an array that holds the previous airport of the current airport, (aka where it came from) 
    distance.resize(sizeOfGraph, INT_MAX); // intialie an array that holds the distance value for each vertex in the graph
    // check to see if all airports are unconnected with each other
    if(airport_map_reduced.size() == 0){
        return std::vector<std::pair<bool, std::string>>();
    }
    //check to see if the start_id is included in the airport map
    std::unordered_map<std::string, Airport>::iterator it = airport_map_reduced.find(start_id);
    if(it == airport_map_reduced.end())
    {
        return std::vector<std::pair<bool, std::string>>();
    }
    Airport start_airport = airport_map_reduced[start_id];
    distance[start_airport.getIndex()] = 0;
    //include an index, with each distance value
    // so know where to find it in the adjacency list
    
    std::priority_queue<std::pair<int, std::string>, std::vector<std::pair<int, std::string>>, compareInt> min_heap;
    //builds heap
    min_heap.push(std::make_pair(0, start_airport.getID()));
    //initialize return vector T
    std::vector<std::pair<bool, std::string>> T(sizeOfGraph, std::pair<bool, std::string>(false, ""));

    while (!min_heap.empty()) {
        std::pair<int, std::string> smallest_route = min_heap.top(); //remove vertix from the graph with the smallest distance between airports
        min_heap.pop();
        //check if in T. if not, add to return vector T. skip otherwise
        std::string dep_id = smallest_route.second;
        int dep_index = airport_map_reduced[dep_id].getIndex();
        if (T[dep_index].first) {
            continue;
        }
        T[dep_index] = std::pair<bool, std::string>(true, dep_id);
        //find neighbors of currently removed vertex
        //list of neighboring edges of smallest element
        std::list<RouteEdge>::iterator it;
        for(it = adj_list_reduced[dep_index].begin(); it != adj_list_reduced[dep_index].end(); it++) {
            if (it == adj_list_reduced[dep_index].begin()) it++;
            if (it == adj_list_reduced[dep_index].end()) break;
            RouteEdge adj = *it;
            std::string dest_id = adj.airport_dest;
            int dest_index = airport_map_reduced[dest_id].getIndex();
            
            if (!T[dest_index].first && distance[dest_index] > adj.distance_km) {
                distance[dest_index] = adj.distance_km;
                min_heap.push(std::make_pair(distance[dest_index], dest_id));
                previous[dest_index] = dep_id;
            }
        }
    }
    std::ofstream mstRoutes;
    mstRoutes.open("MSToutput.txt");
    for (size_t i = 0; i < T.size(); i++) {
      if (T[i].first) {
        mstRoutes << "Route #" << i << ": " << "[" << previous[i] << ", " << T[i].second << "]\n";
      }
    }
    mstRoutes.close();
    return T;
}

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
}
void Graph::reduceRouteList(std::vector<Routes> route_list) {
    std::vector<Routes> new_route_list;
    for (auto route : route_list) {
        if (airport_map_reduced.find(route.getDeparture()) != airport_map_reduced.end() && airport_map_reduced.find(route.getDestination()) != airport_map_reduced.end()) {
            new_route_list.push_back(route);
        }
    }
    route_list_reduced = new_route_list;
}
std::vector<Routes> Graph::getReducedRouteList() {
    return route_list_reduced;
}
std::vector<std::string> Graph::getPreviousVec() {
    return previous;
}
void Graph::printPrimsMST(std::string start_id, std::string save_to) {
    std::vector<Routes> routes;
    
    if(airport_map_reduced.find(start_id) != airport_map_reduced.end()) {
        std::vector<std::pair<bool, std::string>> T;
        //Only go inside this loop if airport exists and included in MST
        std::cout << "Creating PRIM's MST from start point " << start_id << std::endl;
        T = primsMST(start_id);
        int count = 0;
        for (auto t:T) {
            if (t.first) count++;
        }
        std::cout << "Size of T in printPrims(): "<< count << std::endl;


    //     for (size_t i = 0; i < T.size(); i++) {
    //     if (T[i].first) {
    //         std::cout << "Route #" << i << ": " << "[" << prev[i] << ", " << T[i].second << "]" << std::endl;
    //     }
    // }


        //the index of the center or start of MST
        int start_index = airport_map_reduced.find(start_id)->second.getIndex();
        std::vector<std::string> prev = getPreviousVec();
        for(int i = 0; i < (int)T.size(); i++) {
            if(T[i].first) {

                if((airport_map_reduced.find(prev[i]) != airport_map_reduced.end()) && (airport_map_reduced.find(T[i].second) != airport_map_reduced.end())) {
                    Airport current_dep = airport_map_reduced.find(prev[i])->second;
                    int current_dep_id = current_dep.getIndex();
                    Airport current_dest = airport_map_reduced.find(T[i].second)->second;
                    Routes current_route(current_dep, current_dest);
                    routes.push_back(current_route);

                }
            }
        }
    } else {
        std::cout << "The id (" << start_id << ") is not a valid start_id or not included in MST" << std::endl;
    }

    plotgeoMap(routes, save_to);

}

void Graph::initgeoMap() {
    geoMap = new PNG();
    geoMap->readFromFile("mercator_map.png");
    geoMap->scale(3);
}

void Graph::plotgeoMap(std::vector<Routes> routes, std::string save_to, int hue) {

    if(routes.size() == 0)  {
        geoMap->writeToFile(save_to);
        std::cout << "route is empty so no routes were created" << std::endl;
        std::cout << "The number of airports on this map is: " << airport_map_reduced.size() << std::endl;
        std::cout << "The number of routes created on this map is: " << routes.size() << std::endl;
        delete geoMap;
        return;
    }
    std::unordered_map<std::string, Airport>::iterator it;

    for(it = airport_map_reduced.begin(); it != airport_map_reduced.end(); it++) {
        Airport current = it->second;
        std::pair<int, int> map_coordinate = plotOnMap(geoMap, current.getLatitude(), current.getLongitude());

        thickenDot(map_coordinate.first, map_coordinate.second, 0);
    }

    //plot paths of routes
    //HARD CODE AIRPORTS AND ROUTES HERE
    Airport a1;
    Airport a2;
    std::cout << "========================Creating Flight Path========================" << std::endl;
    for(int i = 0; i < (int)routes.size(); i++) {
        if(airport_map_reduced.find(routes[i].getDeparture()) != airport_map_reduced.end()) {
            a1 = airport_map_reduced.find(routes[i].getDeparture())->second;
        }
        if(airport_map_reduced.find(routes[i].getDestination()) != airport_map_reduced.end()) {
            a2 = airport_map_reduced.find(routes[i].getDestination())->second;
        }

        
        std::vector<std::pair<double, double>> path = drawLine(routes[i], 10);
        for(size_t i = 0; i < path.size(); i++) {
            std::pair<int, int> path_coordinate = plotOnMap(geoMap, path[i].first, path[i].second);
            // std::cout << path_coordinate.first << ", " << path_coordinate.second << std::endl;
            HSLAPixel& curr = geoMap->getPixel(path_coordinate.first, path_coordinate.second);
            curr.h = hue;
            curr.s = 1;
            curr.l = 0.5;
        }
    }

    std::cout << 
            "                           ______ " << "\n" <<
            "        _| _~-|___                "<< "\n" <<
            "=  = ==(___CS225__D               "<< "\n" <<
            "            |__|___________________,-~~~~~~~`-.._" << "\n" <<
            "            /     o O o o o o O O o o o o o o O o  |l_ " << "\n" <<
            "            `~-.__        ___..----..                  ) " << "\n" <<
            "                `---~~|___________/------------````` " << "\n" <<
            "                =  ===(_________D " << "\n \n" << "=========================ARRIVAL==========================" << std::endl;

    std::cout << "Flight path creation is done, exporting image...." << std::endl;
    //output the image to the final file
    geoMap->writeToFile(save_to);
    std::cout << "The number of airports on this map is: " << airport_map_reduced.size() << std::endl;
    std::cout << "The number of routes created on this map is: " << routes.size() << std::endl;
    // delete geoMap;
    delete geoMap;
}
void Graph::plotgeoMap(std::vector<Routes> routes, std::string save_to) {
    plotgeoMap(routes, save_to, 120);
}


void Graph::thickenDot(int x, int y, int hue) {
    // color the pixels in a 3x3 square so airports and routes are more visible
    for (int i = x-1; i < x + 2; i++) {
        for (int  j = y-1; j < y + 2; j++) {
            HSLAPixel& curr = geoMap->getPixel(i,j);
            curr.h = hue;
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

std::vector<std::pair<double, double>> Graph::drawLine(Routes route, int n) {
    Airport a1;
    Airport a2;
    if(airport_map_reduced.find(route.getDeparture()) != airport_map_reduced.end()) {
        a1 = airport_map_reduced.find(route.getDeparture())->second;
    }
    if(airport_map_reduced.find(route.getDestination()) != airport_map_reduced.end()) {
        a2 = airport_map_reduced.find(route.getDestination())->second;
    }
    
    std::vector<double> threeDCoord1 = cart_coordinates(a1.getLatitude(), a1.getLongitude());
    std::vector<double> threeDCoord2 = cart_coordinates(a2.getLatitude(), a2.getLongitude());

    std::vector<double> unit_product;

    std::vector<std::pair<double, double>> recorded_path;
    std::vector<double> current = threeDCoord1;

    
    bool not_arrived = true;
    //set i boundary by calculating the distance between to come up with optimal sample size
    
    for (int i = 0; i < 8000; i++) {
        unit_product = findVec(current, threeDCoord2);
        current[0] += unit_product[0] * n;
        current[1] += unit_product[1] * n;
        current[2] += unit_product[2] * n;
        normalize(current);
        if(getDistance(current, threeDCoord2) < 10) {

            break;
        }
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

std::vector<double> Graph::cart_coordinates(double lat_, double long_) {
    std::vector<double> coordinates;
    double pi = 2 * acos(0.0);
    //calculates the 3D cartesian coordinates of the lat long
    // const double re = 6378.1; //in kilo-meters
    const double re = 6378.1;
    double phi = lat_*pi/180;
    double lda = long_*pi/180;
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

    double neg = 1.0;
    if(y < 0) {
        neg = -1.0;
    }
    double lda = neg*acos((x/(re * cos(phi))));
    double lat_ = phi * 180 / pi;
    double long_ = lda * 180 / pi;

    //=====================FOR BUG FIXES====================//
    // std::cout << std::endl;
    // std::cout << "===================================================" << std::endl;
    // std::cout << "phi = " << phi << std::endl;
    // std::cout << "lda = " << lda << std::endl;
    // std::cout << "x,y,z" << x << ", " << y << ", " << z << std::endl;
    // std::cout << "===================================================" << std::endl;
    // std::cout << "printing lat_ " << lat_ <<std::endl;
    // std::cout << "printing long_ " << long_ <<std::endl;
    lat_long.first = lat_;
    lat_long.second = long_;

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
    //for i component
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


std::vector<std::string> Graph::BFS(Airport start, Airport end) { //"YXU" "YYC"
  if (airport_map_reduced[start.getID()].getID() == "" || airport_map_reduced[end.getID()].getID() == "") {
    std::cout << "Start and/or end Airport does not exist in airport map" << std::endl;
    return std::vector<std::string>();
  }

  if (start.getID() == end.getID()) {
    std::cout << "Start and end Airport is " << start.getID() << ". You can not create a route from same start and end point" << std::endl;
    return std::vector<std::string>();
  }

  if ((start.getLatitude() == end.getLatitude()) && (start.getLongitude() == end.getLongitude())) {
    std::cout << "Start and end Airport has the same geographic location" << std::endl;
    return std::vector<std::string>();
  }
  std::vector<std::string> path;
  std::unordered_map<std::string, std::string> pathMap;
  std::vector<bool> visited;
  // initialize a vector of booleans to keep track of which airports have been visited
  visited.resize(airport_map_reduced.size(), false);
  std::queue<std::list<RouteEdge>::iterator> queue;
  int startIndex = start.getIndex();
  std::list<RouteEdge>::iterator it = adj_list_reduced[startIndex].begin();
  queue.push(it);
  // set the starting Airport to visited
  visited[startIndex] = true;
  while (!queue.empty()) {
    std::list<RouteEdge>::iterator current = queue.front();
    std::list<RouteEdge>::iterator it = current;
    queue.pop();
    // check if the RouteEdge is not the departure Airport
    if (it->distance_km > 0) {
        Airport temp_airport = airport_map_reduced[it->airport_dest];
        it = adj_list_reduced[temp_airport.getIndex()].begin();
        pathMap[it->airport_dest] = current->airport_dep;
    }
    // check if we have found what we are looking for
    if (it->airport_dest == end.getID()) {
      std::string currentAirport = pathMap[end.getID()];
      path.push_back(end.getID());
      // add all airports in the map to a vector output of BFS in reverse order, and then reverse to get the output
      while (currentAirport != start.getID()) {
        path.push_back(currentAirport);
        currentAirport = pathMap[currentAirport];
      }

      path.push_back(start.getID());
      reverse(path.begin(), path.end());
      return path;
    }
    
    int new_index = airport_map_reduced[it->airport_dep].getIndex();
    it++;
    while (it != adj_list_reduced[new_index].end()) {
      // add iterators to the current airports neighbors to the queue
      int index = airport_map_reduced[it->airport_dest].getIndex();
      if (!visited[index]) {
        pathMap[it->airport_dest] = current->airport_dest;
        visited[index] = true;
        queue.push(it);
      }
      it++;
    }
  }
  return std::vector<std::string>();
}

std::unordered_map<std::string, Airport> Graph::getReducedMap() {
 return airport_map_reduced;
}


std::vector<Routes> Graph::BFSRouteConvert(std::vector<std::string> airports) {
  std::vector<Routes> output;
  // iterate through the vector of airports and create a route between consecutive airports
  for (unsigned i = 0; i < airports.size() - 1; i++) {
    Airport dep = airport_map_reduced[airports[i]];
    Airport dest = airport_map_reduced[airports[i + 1]];
    Routes converted = Routes(dep, dest);
    // add the created route to a vector of routes
    output.push_back(converted);
  }
  return output;
}

std::vector<Airport> Graph::getDestinations(int index) { // *****add comments*****
  std::vector<Airport> destinations;
  std::list<RouteEdge>::iterator it;
  for (it = adj_list_reduced[index].begin(); it != adj_list_reduced[index].end(); it++) {
    Airport current = airport_map_reduced[it->airport_dest];
    destinations.push_back(current);
  }
  return destinations;
}


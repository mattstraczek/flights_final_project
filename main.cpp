#include "routes.h"
#include "airport.h"
#include "parsing.h"
#include "graph.h"
#include <iostream>
#include <vector>

int main() {
    Parsing parse;
    parse.extractAirports("airports.txt");
    std::vector<Routes> list = parse.extractRoutes("routes.txt");
    //std::cout << "hello" << std::endl;

    //std::cout << list.empty() << std::endl;

    // for(Routes route : list) {
    //     std::cout << route.getDeparture() << " --> " << route.getDestination() << std::endl;
    // }
    std::unordered_map<std::string, Airport> airport_map = parse.getAirportMap();
<<<<<<< HEAD
    std::cout << list[0].getDeparture() << std::endl;
    std::cout << airport_map[list[0].getDeparture()].getID() << std::endl;
    Graph graph(airport_map, list);


=======
    
    Graph graph(airport_map, list);
    std::cout << "Size of Routes: " << list.size() << std::endl;
>>>>>>> 0e6bad39adc07231e5aa33a246782eb6a305537f
	graph.printRouteMatrixLimited(10);
    graph.writeRouteMatrixToFile();

    //testing reduce matrix
    graph.reduceAirportMap(list);
    graph.reduceAirportMatrix(list);
    graph.writeReducedMatrixToFile();
}


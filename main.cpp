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
    
    Graph graph(airport_map, list);
    std::cout << "Size of Routes: " << list.size() << std::endl;
    graph.writeAdjListToFile();
	// graph.printRouteMatrixLimited(10);
    // graph.writeRouteMatrixToFile();

    //testing reduce matrix
    // graph.reduceAirportMap(list);
    // graph.reduceAirportMatrix(list);
    // graph.writeReducedMatrixToFile();
    //graph.initgeoMap();
    //graph.plotgeoMap();
    std::vector<std::string> vec;
    vec = graph.BFS(graph.getReducedMap()["YXU"], graph.getReducedMap()["YYC"]);
    // for (auto airport : vec) {
    //     std::cout << airport << std::endl;
    // }
    // vec = graph.BFS(graph.getReducedMap()["YXU"], graph.getReducedMap()["ORD"]);
    //vec = graph.BFS(graph.getReducedMap()["YXU"], graph.getReducedMap()["YXJ"]);
    //vec = graph.BFS(graph.getReducedMap()["YXU"], graph.getReducedMap()["YYE"]);
    //vec = graph.BFS(graph.getReducedMap()["YXU"], graph.getReducedMap()["YDQ"]);
    vec = graph.BFS(graph.getReducedMap()["ZVK"], graph.getReducedMap()["CEB"]);
    graph.initgeoMap();
// <<<<<<< HEAD
//     graph.plotgeoMap();
//     // std::vector<std::string> vec;
//     // vec = graph.BFS(graph.getReducedMap()["YXU"], graph.getReducedMap()["YYC"]);
// =======
    std::vector<Routes> routes = graph.BFSRouteConvert(vec);
    for (unsigned i = 0; i < routes.size(); i++) {
      std::cout << routes[i].getDeparture() << std::endl;
    }
    graph.plotgeoMap(routes);
//    graph.initgeoMap();
//    graph.plotgeoMap(graph.getReducedRouteList());
// >>>>>>> 5f96e5f32efebecb70bc1e948e8da9651e89f29b
}


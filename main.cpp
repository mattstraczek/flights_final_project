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
    std::cout << "Size of Reduced Routes: " << graph.getReducedRouteList().size() << std::endl;
    //graph.writeAdjListToFile();
	// graph.printRouteMatrixLimited(10);
    // graph.writeRouteMatrixToFile();

    //testing reduce matrix
    // graph.reduceAirportMap(list);
    // graph.reduceAirportMatrix(list);
    // graph.writeReducedMatrixToFile();
    //graph.initgeoMap();
    //graph.plotgeoMap();
    std::vector<std::string> vec;
    // vec = graph.BFS(graph.getReducedMap()["YXU"], graph.getReducedMap()["YYC"]);
    // // for (auto airport : vec) {
    // //     std::cout << airport << std::endl;
    // // }
    // vec = graph.BFS(graph.getReducedMap()["YXU"], graph.getReducedMap()["ORD"]);
    // vec = graph.BFS(graph.getReducedMap()["YXU"], graph.getReducedMap()["YXJ"]);
    // vec = graph.BFS(graph.getReducedMap()["YXU"], graph.getReducedMap()["YYE"]);
    // vec = graph.BFS(graph.getReducedMap()["YXU"], graph.getReducedMap()["YDQ"]);
    // vec = graph.BFS(graph.getReducedMap()["ZVK"], graph.getReducedMap()["CEB"]);
    // std::vector<bool> T;
    // T = graph.primsMST("ORD");
    // std::vector<Routes> primRoute;
    // int count = 0;
    // for (size_t i = 0; i < T.size(); i++) {
    //     std::cout << T[i] << std::endl;
    //     if (T[i]) {
    //         count++;
    //         primRoute.push_back(graph.getReducedRouteList()[i]);
    //     }
    // }
    graph.initgeoMap();
<<<<<<< HEAD
    //graph.plotgeoMap(graph.getReducedRouteList(), "geographic_map.png");
=======
//    graph.plotgeoMap(graph.getReducedRouteList(), "geographic_map.png");
>>>>>>> 07ed7e61c678e91f44c64229f11369ca04950f37
    // ///***************Constructing routes from Prims*******************
    // std::vector<std::pair<bool, std::string>> T;
    // T = graph.primsMST("ORD");

    // std::vector<std::string> prev = graph.getPreviousVec();

    // size_t starting_idx = graph.getReducedMap()["ORD"].getIndex();

    // for (size_t i = 0; i < T.size(); i++) {
    //     if (T[i].first) {
    //         std::cout << "Route #" << i << ": " << "[" << prev[i] << ", " << T[i].second << "]" << std::endl;
    //     }
    // }
    // ///***************Constructing routes from Prims*******************

    // graph.plotgeoMap(primRoute);
<<<<<<< HEAD
    // graph.plotgeoMap(primRoute, "geographic_map.png");
    //****graph.printPrimsMST("GEA", "geographic_map.png");
=======
    std::vector<std::string> bfsroute = graph.BFS(airport_map.find("ORD")->second, airport_map.find("NOU")->second);
    std::vector<Routes> shortest_route = graph.BFSRouteConvert(bfsroute);
    Airport lax = airport_map.find("LAX")->second;
    Airport nou = airport_map.find("NOU")->second;
    Airport nrt = airport_map.find("NRT")->second;
    Airport bne = airport_map.find("BNE")->second;
    Airport ord = airport_map.find("ORD")->second;
    
    Routes r1(ord, lax);
    Routes r2(lax, bne);
    Routes r3(bne, nou);

    std::vector<Routes> routes;

    routes.push_back(r1);
    routes.push_back(r2);
    routes.push_back(r3);
    // graph.printPrimsMST("ORD", "geographic_map.png");
    graph.plotgeoMap(routes, "geographic_map1.png");
    graph.plotgeoMap(shortest_route, "geographic_map2.png", 0);
    
>>>>>>> 07ed7e61c678e91f44c64229f11369ca04950f37
    // std::cout << "Number of vertices in MST: " << count << std::endl;
    // std::cout << "Verify routes in primRoute: " << primRoute.size() << std::endl;




    ///Geo things
//     vec = graph.BFS(graph.getReducedMap()["YXU"], graph.getReducedMap()["YYC"]);
//     // for (auto airport : vec) {
//     //     std::cout << airport << std::endl;
//     // }
//     // vec = graph.BFS(graph.getReducedMap()["YXU"], graph.getReducedMap()["ORD"]);
//     //vec = graph.BFS(graph.getReducedMap()["YXU"], graph.getReducedMap()["YXJ"]);
//     //vec = graph.BFS(graph.getReducedMap()["YXU"], graph.getReducedMap()["YYE"]);
//     //vec = graph.BFS(graph.getReducedMap()["YXU"], graph.getReducedMap()["YDQ"]);
//     vec = graph.BFS(graph.getReducedMap()["ZVK"], graph.getReducedMap()["CEB"]);
//     graph.initgeoMap();
// // <<<<<<< HEAD
// //     graph.plotgeoMap();
// //     // std::vector<std::string> vec;
// //     // vec = graph.BFS(graph.getReducedMap()["YXU"], graph.getReducedMap()["YYC"]);
// // =======
//     std::vector<Routes> routes = graph.BFSRouteConvert(vec);
//     for (unsigned i = 0; i < routes.size(); i++) {
//       std::cout << routes[i].getDeparture() << std::endl;
//     }
    // graph.plotgeoMap(routes);
//    graph.initgeoMap();
//    graph.plotgeoMap(graph.getReducedRouteList());
// // >>>>>>> 5f96e5f32efebecb70bc1e948e8da9651e89f29b
}


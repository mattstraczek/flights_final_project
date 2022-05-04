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
    airport_map = graph.getReducedMap();

    char c;
    std::cout << "What would you like to run?" << std::endl;
    std::cout << "a. Prim's" << std::endl;
    std::cout << "b. BFS" << std::endl;
    std::cout << "c. Plot a single, direct route" << std::endl;
    std::cout << "d. Quit" << std::endl;
    std::cout << "Enter a, b, c, or d: ";
    std::cin >> c;
    if (c == 'a') {
      std::string id;
      std::cout << "Please enter a starting airport ID (example: ORD, LAX): ";
      std::cin >> id;
      Airport airport = (graph.getReducedMap())[id];
      if (airport.getID() == "") {
        std::cout << "Airport does not exist, exiting..." << std::endl;
        return 0;
      }
      graph.initgeoMap();
      graph.printPrimsMST(airport.getID(), "geographic_map.png");
      std::cout << "Prim's output image saved to geographic_map.png" << std::endl;
      std::vector<std::pair<bool, std::string>> T;
      T = graph.primsMST(airport.getID());
      std::vector<std::string> prev = graph.getPreviousVec();
      size_t starting_idx = graph.getReducedMap()[airport.getID()].getIndex();
      std::ofstream prims;
      prims.open("text_output.txt");
      for (size_t i = 0; i < T.size(); i++) {
        if (T[i].first) {
          prims << "Route #" << i << ": " << "[" << prev[i] << ", " << T[i].second << "]" << std::endl;
        }
      }
      std::cout << "All MST routes are exported to text_output.txt" << std::endl;
      return 0;;
    } else if (c == 'b') {
      std::string start;
      std::string end;
      std::cout << "Please enter a starting airport ID (example: ORD, LAX): ";
      std::cin >> start;
      Airport dep = graph.getReducedMap()[start];
      if (dep.getID() == "") {
        std::cout << "Airport does not exist, exiting..." << std::endl;
        return 0;
      }
      std::cout << "Please enter an ending airport ID (example: ORD, LAX): ";
      std::cin >> end;
      Airport dest = graph.getReducedMap()[end];
      if (dest.getID() == "") {
        std::cout << "Airport does not exist, exiting..." << std::endl;
        return 0;
      }
      std::vector<std::string> airports = graph.BFS(dep, dest);
      if (airports.size() == 0) {
        std::cout << "BFS did not find a path from the start to end airport, meaning they are unconnected. Exiting..." << std::endl;
        return 0;
      }
      std::ofstream output;
      output.open("text_output.txt");
      for (unsigned i = 0; i < airports.size(); i++) {
        output << airports[i] << std::endl;
      }
      std::vector<Routes> routes = graph.BFSRouteConvert(airports);
      graph.initgeoMap();
      graph.plotgeoMap(routes, "geographic_map.png");
      std::cout << "BFS output image saved to geographic_map.png" << std::endl;
      std::cout << "BFS airports are exported to text_output.txt" << std::endl;
      return 0;
    } else if (c == 'c') {
      std::string start;
      std::cout << "Please enter a starting airport ID (example: ORD, LAX): ";
      std::cin >> start;
      Airport dep = graph.getReducedMap()[start];
      if (dep.getID() == "") {
        std::cout << "Airport does not exist, exiting..." << std::endl;
        return 0;
      }
      std::string end;
      std::cout << "Please enter an ending airport ID (example: ORD, LAX): ";
      std::cin >> end;
      Airport dest = graph.getReducedMap()[end];
      if (dest.getID() == "") {
        std::cout << "Airport does not exist, exiting..." << std::endl;
        return 0;
      }
      std::vector<Airport> destinations = graph.getDestinations(dep.getIndex());
      bool exists = false;
      for (unsigned i = 0; i < destinations.size(); i++) {
        if (destinations[i].getID() == dest.getID()) {
          exists = true;
          break;
        }
      }
      if (!exists) {
        std::cout << "A direct route between these two airports does not exist, exiting..." << std::endl;
        return 0;
      }
      else {
        Routes route(dep, dest);
        std::vector<Routes> routes;
        routes.push_back(route);
        graph.initgeoMap();
        graph.plotgeoMap(routes, "geographic_map.png");
        std::cout << "Route plotted and saved in geographic_map.png" << std::endl;
      }
      return 0;
    } else if (c == 'd') {
      return 0;
    } else {
      std::cout << "Invalid input, exiting..." << std::endl;
      return 0;
    }
    //graph.writeAdjListToFile();
	// graph.printRouteMatrixLimited(10);
    // graph.writeRouteMatrixToFile();

    //testing reduce matrix
    // graph.reduceAirportMap(list);
    // graph.reduceAirportMatrix(list);
    // graph.writeReducedMatrixToFile();
    //graph.initgeoMap();
    //graph.plotgeoMap();
//    std::vector<std::string> vec;
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
//    graph.initgeoMap();
//<<<<<<< HEAD
    //graph.plotgeoMap(graph.getReducedRouteList(), "geographic_map.png");
//=======
//    graph.plotgeoMap(graph.getReducedRouteList(), "geographic_map.png");
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
    // graph.plotgeoMap(primRoute, "geographic_map.png");
    //****graph.printPrimsMST("GEA", "geographic_map.png");
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


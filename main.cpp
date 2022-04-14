#include "routes.h"
#include "airport.h"
#include "parsing.h"
#include "graph.h"
#include <iostream>
#include <vector>

int main() {
    Parsing parse;

    std::vector<Routes> list = parse.extractRoutes("routes.txt");
    std::cout << "hello" << std::endl;

    std::cout << list.empty() << std::endl;

    for(Routes route : list) {
        std::cout << "hello" << std::endl;
        std::cout << route.getDeparture() << " --> " << route.getDestination() << std::endl;
    }
    
}
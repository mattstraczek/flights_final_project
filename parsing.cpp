#include <fstream>
#include "parsing.h"
#include <map>

Parsing::Parsing() {
  
}
vector<string> Parsing::parseLine(string line) {
    vector<string> parsed;
    string curr;

    for(char x : line) {
        if(x == ',') {
            parsed.push_back(curr);
            curr = "";
        } else {
            curr += x;
        }
    }
    return parsed;
}
Airport Parsing::createAirport(vector<string> line) {
  string id_ = line[4].substr(1, 3);
  double lat_ = std::stod(line[6]);
  double long_ = std::stod(line[7]);
  int index = airport_map.size();
  Airport airport = Airport(id_, lat_, long_, index);
  return airport;
}

bool Parsing::isInUS(vector<string> line) {
  string country = line[3].substr(1, line[3].size() - 2);
  if (country == "United States") {
    return true;
  }
  return false;
}

void Parsing::extractAirports(string fileName) {
  FILE * data = fopen(fileName.c_str(), "r");
  string line = "";

  ifstream myAirports(fileName);
  if(myAirports.is_open()) {
      while(getline(myAirports, line)) {
        // std::cout << line << std::endl;
          vector<string> parsed = parseLine(line);
          // std::cout << "country is ";
          // std::cout << parsed[3] << std::endl;
          if(isInUS(parsed)) {
            Airport airport = createAirport(parsed);
            if(airport_map.find(airport.getID()) == airport_map.end()) {
              airport_map[airport.getID()] = airport;
            }
          }
      }
      myAirports.close();
  }
}


void Parsing::writeAirports(string fileName) {
  ofstream USAirports;
  USAirports.open(fileName);

  unordered_map<string, Airport>::iterator it;

  for(it = airport_map.begin(); it != airport_map.end(); it++) {
    Airport current = (*it).second;
    USAirports << current.getID() << "," << current.getLatitude() << "," << current.getLongitude() << "\n";
  }
  USAirports.close();
}
/**
 * @brief all the United States routes are extracted
 * 
 * @param fileName 
 * @return vector<Routes> 
 */
vector<Routes> Parsing::extractRoutes(string fileName) {
  string line;
  vector<Routes> routeList;
  ifstream myroutes(fileName);
  if(myroutes.is_open()) {
      while(getline(myroutes, line)) {
        // std::cout << line << std::endl;
          vector<string> parsed = parseLine(line);
          //should sort or decide whether the airports both are in the US
          if((airport_map.find(parsed[2]) != airport_map.end()) && (airport_map.find(parsed[4]) != airport_map.end())) {
              //that means the airport exists in the map, only then I can add 
              Routes route = createRoutes(parsed);
              string routeID = route.getDeparture() + route.getDestination();
              if(route_map.find(routeID) == route_map.end()) {

                //420 means that it exists
                route_map[routeID] = 420;
                routeList.push_back(route);
              }
          }
          

      }
      myroutes.close();
  }
  return routeList;
}
Routes Parsing::createRoutes(vector<string> data) {
    
    Routes route(airport_map.find(data[2])->second, airport_map.find(data[4])->second);
    
    return route;
}

std::unordered_map<std::string, Airport> Parsing::getAirportMap() {
  return airport_map;
}

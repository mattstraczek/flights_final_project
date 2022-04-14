#include <fstream>
#include "parsing.h"

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
  Airport airport = Airport(id_, lat_, long_);
  return airport;
}

bool Parsing::isInUS(vector<string> line) {
  string country = line[3].substr(1, line[3].size() - 2);
  if (country == "United States") {return true;}
  return false;
}

vector<Airport> Parsing::extractAirports(string fileName) {
  vector<Airport> airports;
  FILE * data = fopen(fileName.c_str(), "r");
  string line = "";
  while(!feof(data)) {
    line.push_back(getc(data));
    if (getc(data) == '\n') {
      vector<string> converted = parseLine(line);
      if (isInUS(converted)) {
        Airport airport = createAirport(converted);
        airports.push_back(airport);
      }
      line = "";
    }
  }
  fclose(data);
  return airports;
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
            vector<string> parsed = parseLine(line);
            //should sort or decide whether the airports both are in the US
            if((airport_map.find(parsed[2]) != airport_map.end()) && (airport_map.find(parsed[4]) != airport_map.end())) {
                //that means the airport exists in the map, only then I can add 
                routeList.push_back(createRoutes(parsed));
            }

        }
        myroutes.close();
    }
  return routeList;
}
Routes Parsing::createRoutes(vector<string> data) {
    
    //Routes route(airport_map.find(data[2])->second, airport_map.find(data[4])->second);
    Routes route;
    return route;
}



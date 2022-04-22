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
  //ASCII Values:
  //"-": 45
  //".": 46
  //"0-9": 48-57
  //"a-z": 97-122
  //"A-Z": 65-90
  bool valid_data = true;

  //check that line.size() == 14
//  if (line.size() != 14) return Airport(); *******WE ONLY CARE ABOUT CRITICAL IDENTIFIERS AS PER PROPOSAL, BUT NECESSARY FOR FORMAT CHECK************

  //Check that id is 3 chars
  //Check that id is string
  //Check that all chars are uppercase and letters
  if (line[4].size() != 5) return Airport();
  string id_ = line[4].substr(1, 3);
  for (size_t i = 0; i < 3; i++) {
    if (id_[i] < 65 || id_[i] > 90) {
      valid_data = false;
      break;
    }
  }
  if (!valid_data) return Airport();

  //double lat_ = std::stod(line[6]);
  //check that its a double (iterate through chars and make sure that are chars between "0-9", ".", or "-")
  //iterating process:
  //1.check if "-" is first
  //a. whether it is or isnt, make sure it never appears again: -0.908 yes, 0-.908 no, 0.9-08 no
  //2. 0.9, 10.9, -0.9, -10.9 -> only one period in the string, and only in positions 1, 2, 3 (0-indexed) : -.1
  //3. check in range [-90, 90]
  std::string lat_str = line[6];
  bool duplicate_periods = false;
  int index_period = -1;

  for (size_t i = 0; i < lat_str.size(); i++) {
    if (lat_str[i] == '.') {
      if (duplicate_periods) {
        valid_data = false;
      }
      duplicate_periods = true;
      index_period = i;
    }
  }
  if (index_period == 0) return Airport();
  if (!valid_data || !duplicate_periods) return Airport();

  bool duplicate_hyphens = false;
  int index_hyphen = -1;

  for (size_t i = 0; i < lat_str.size(); i++) {
    if (lat_str[i] == '-') {
      if (duplicate_hyphens) {
        valid_data = false;
      }
      duplicate_hyphens = true;
      index_hyphen = i;
    }
  }
  if (!(index_hyphen == 0 || index_hyphen == -1)) return Airport();
  if (!valid_data) return Airport();

  //0.9
  if (index_period == 1) {
    if (!(lat_str[0] >= 48 && lat_str[0] <= 57)) {
      valid_data = false;
    }
  }
  //10.9, -0.9
  if (index_period == 2) {
    if (lat_str[0] == '-') {
      if(lat_str[1] < 48 || lat_str[1] > 57) {
        valid_data = false;
      }
    } else if (lat_str[0] >= 48 && lat_str[0] <= 57) {
      if (lat_str[1] < 48 || lat_str[1] > 57) {
        valid_data = false;
      }
    } else {
      valid_data = false;
    }
  }
  //-10.9
  if (index_period == 3) {
    if (lat_str[0] != '-') {
      valid_data = false;
    }
    if (lat_str[1] < 48 || lat_str[1] > 57) {
      valid_data = false;
    }
    if (lat_str[2] < 48 || lat_str[2] > 57) {
      valid_data = false;
    }
  }

  if (!valid_data) return Airport();

  for (size_t i = index_period + 1; i < lat_str.size(); i++) {
    if (lat_str[i] < 48 || lat_str[i] > 57) {
      valid_data = false;
      break;
    }
  }

  if (!valid_data) return Airport();

  double lat_ = std::stod(line[6]);
  if (lat_ < -90.0 || lat_ > 90) {
    return Airport();
  }

  //check if its in range [-90, 90]

  //double long_ = std::stod(line[7]);
  //check that its a double (iterate through chars and make sure that are chars between "0-9", ".", or "-")
  //iterating process:
  //1.check if "-" is first
  //a. whether it is or isnt, make sure it never appears again: -0.908 yes, 0-.908 no, 0.9-08 no
  //2. 0.9, 10.9, 109.5, -0.9, -10.9, -109.5 -> only one period in the string, and only in positions 1, 2, 3, 4 (0-indexed) : -.1
  //3. check in range [-90, 90]
  std::string long_str = line[7];
  duplicate_periods = false;
  index_period = -1;
<<<<<<< HEAD
=======

>>>>>>> bcf85633f935f0dff03f7de402b0b7695e57a368
  for (size_t i = 0; i < long_str.size(); i++) {
    if (long_str[i] == '.') {
      if (duplicate_periods) {
        valid_data = false;
      }
      duplicate_periods = true;
      index_period = i;
    }
  }
<<<<<<< HEAD
=======

>>>>>>> bcf85633f935f0dff03f7de402b0b7695e57a368
  if (index_period == 0) return Airport();
  if (!valid_data || !duplicate_periods) return Airport();
 
  duplicate_hyphens = false;
  index_hyphen = -1;

  for (size_t i = 0; i < lat_str.size(); i++) {
    if (lat_str[i] == '-') {
      if (duplicate_hyphens) {
        valid_data = false;
      }
      duplicate_hyphens = true;
      index_hyphen = i;
    }
  }
  if (!(index_hyphen == 0 || index_hyphen == -1)) return Airport();
  if (!valid_data) return Airport();

  //0.9
  if (index_period == 1) {
    if (!(long_str[0] >= 48 && long_str[0] <= 57)) {
      valid_data = false;
    }
  }
  //10.9, -0.9
  if (index_period == 2) {
    if (long_str[0] == '-') {
      if(long_str[1] < 48 || long_str[1] > 57) {
        valid_data = false;
      }
    } else if (long_str[0] >= 48 && long_str[0] <= 57) {
      if (long_str[1] < 48 || long_str[1] > 57) {
        valid_data = false;
      }
    } else {
      valid_data = false;
    }
  }
  //109.5, -10.9, 
  if (index_period == 3) {
    if (long_str[0] == '-') {
      if(long_str[1] < 48 || long_str[1] > 57) {
        valid_data = false;
      }
      if(long_str[2] < 48 || long_str[2] > 57) {
        valid_data = false;
      }
    } else if (long_str[0] >= 48 && long_str[0] <= 57) {
      if (long_str[1] < 48 || long_str[1] > 57) {
        valid_data = false;
      }
      if(long_str[2] < 48 || long_str[2] > 57) {
        valid_data = false;
      }
    } else {
      valid_data = false;
    }
  }
  //-109.5
  if (index_period == 4) {
    if (long_str[0] != '-') {
      valid_data = false;
    }
    if (long_str[1] < 48 || long_str[1] > 57) {
      valid_data = false;
    }
    if (long_str[2] < 48 || long_str[2] > 57) {
      valid_data = false;
    }
    if (long_str[3] < 48 || long_str[3] > 57) {
      valid_data = false;
    }
  }

  if (!valid_data) return Airport();

  for (size_t i = index_period + 1; i < long_str.size(); i++) {
    if (long_str[i] < 48 || long_str[i] > 57) {
      valid_data = false;
      break;
    }
  }

  if (!valid_data) return Airport();

  double long_ = std::stod(line[7]);
  if (long_ < -180.0 || long_ > 180) {
    return Airport();
  }

  //check if its in range [-180 <-> 180]
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
  /*FILE * data = fopen(fileName.c_str(), "r");*/
  string line = "";
  ifstream myAirports(fileName);
  if(myAirports.is_open()) {
      while(getline(myAirports, line)) {
        // std::cout << line << std::endl;
          vector<string> parsed = parseLine(line);
          //if(isInUS(parsed)) { //***DELETE THIS***
          Airport airport = createAirport(parsed);
          if (airport.getID() != "") {//, data is invalid so skip this ***ADD THIS***
            if(airport_map.find(airport.getID()) == airport_map.end()) {
              airport_map[airport.getID()] = airport;
            }
          }
      }
      myAirports.close();
  }
  std::unordered_map<std::string, Airport>::iterator it;
  for (it = airport_map.begin(); it != airport_map.end(); it++) {
    Airport current = (*it).second;
//    std::cout << current.getID() << std::endl;
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
              //if route == Routes(), data is invalid so skip ***ADD THIS***
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
  //ASCII Values:
  //"-": 45
  //".": 46
  //"0-9": 48-57
  //"a-z": 97-122
  //"A-Z": 65-90
  bool valid_data = true;
  if (data.size() != 9) return Routes(); //Added for format check

  std::string DEP = data[2];
  //Check that id is 3 chars
  //Check that id is string
  //Check that all chars are uppercase and letters
  if (DEP.size() != 3) return Routes();
  for (size_t i = 0; i < 3; i++) {
    if (DEP[i] < 65 || DEP[i] > 90) {
      valid_data = false;
      break;
    }
  }
  if (!valid_data) return Routes();

  std::string DEST = data[4];
  //Check that id is 3 chars
  //Check that id is string
  //Check that all chars are uppercase and letters
  if (DEST.size() != 3) return Routes();
  for (size_t i = 0; i < 3; i++) {
    if (DEST[i] < 65 || DEST[i] > 90) {
      valid_data = false;
      break;
    }
  }
  if (!valid_data) return Routes();

  Routes route(airport_map.find(DEP)->second, airport_map.find(DEST)->second);
  
  return route;
}

std::unordered_map<std::string, Airport> Parsing::getAirportMap() {
  return airport_map;
}

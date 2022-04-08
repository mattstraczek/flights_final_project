#include <fstream>
#include "parsing.h"

vector<string> Parsing::parseLine(string line) {
    vector<string> parsed;
    string curr;

    for(char x : line) {
        if(x == ',') {
            parsed.push_back(curr);
        } else {
            curr += x;
        }
    }
    return parsed;
}
//extractRoutes
//for this we need a map of airports created

// Airport Parsing::createAirport(vector<string> line) {
//   string id = line[4].substr(1, 3);
//   double lat = line[6];
//   double long = line[7];
//   Airport airport = Airport(id, lat, long);
//   return airport;
// }

// bool Parsing::isInUS(vector<string> line) {
//   string country = line[3].substr(1, line[3].size() - 2);
//   if (country == "United States") {return true;}
//   return false;
// }

// vector<Airport> Parsing::extractAirports(string fileName) {
//   vector<Airport> airports;
//   FILE * data = fopen(fileName.c_str(), "r");
//   string line = "";
//   while(!feof(data)) {
//     line.push_back(getc(data));
//     if (getc(data) == '\n') {
//       vector<string> converted = extractLineInfo(line);
//       if (isInUS(converted)) {
//         Airport airport = createAirport(converted);
//         airports.push_back(airport);
//       }
//       line = "";
//     }
//   }
//   fclose(data);
// }
#include "airport.h"
#include <string>
using namespace std;

Airport::Airport() {
    latitude = 0;
    longitude = 0;
    ID = "";
}

Airport::Airport(string id, double lat, double longi) {
    setID(id);
    setLatitude(lat);
    setLongitude(longi);
}

void Airport::setLatitude(double lat_) {
    latitude = lat_;
}
void Airport::setLongitude(double long_) {
    longitude = long_;
}
void Airport::setID(std::string id) {
    ID = id;
}
double Airport::getLatitude() {
    return latitude;
}
double Airport::getLongitude() {
    return longitude;
}
std::string Airport::getID() {
    return ID;
}
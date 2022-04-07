#include "airport.h"
double Airport::getLatitude() {
    return latitude;
}
double Airport::getLongitude() {
    return longitude;
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
std::string Airport::getID() {
    return ID;
}
#include "routes.h"
#include <math.h>

Routes::Routes() {
    departure_ = Airport();
    destination_ = Airport();
    distance_ = 0.0;
}
Routes::Routes(Airport dep, Airport dest) {
    departure_ = dep;
    destination_ = dest;
    distance_ = calculateDistance(departure_, destination_);
}
/**
 * @brief calculates the distance between the routes departure and destination 
 * 
 * @param dep 
 * @param dest 
 * 
 * @return double
 */
double Routes::calculateDistance(Airport dep, Airport dest) {
    return getDistance(cart_coordinates(dep.getLatitude(), dep.getLongitude()), cart_coordinates(dest.getLatitude(), dest.getLongitude()));
}


std::vector<double> Routes::cart_coordinates(double lat1, double long1) {
    std::vector<double> coordinates;
    double pi = 2 * acos(0.0);
    //calculates the 3D cartesian coordinates of the lat long
    // const double re = 6378.1; //in kilo-meters
    const double re = 6378.1;
    double phi = lat1*pi/180;
    double lda = long1*pi/180;
    double x = re * cos(phi) * cos(lda);
    double y = re * cos(phi) * sin(lda);
    double z = re * sin(phi);
    
    coordinates.push_back(x);
    coordinates.push_back(y);
    coordinates.push_back(z);
    
    return coordinates;
}


double Routes::getMagnitude(std::vector<double> loc) {
    double mag = sqrt(loc[0]*loc[0] + loc[1]*loc[1] + loc[2]*loc[2]);
    return mag;
}
    
double Routes::getDistance(std::vector<double> loc1, std::vector<double> loc2) {
    //get dot product first
    const double pi = 2 * acos(0.0);
    
    const double re = 6378.1; //in kilo-meters

    double dotProduct = loc1[0]*loc2[0] + loc1[1]*loc2[1] + loc1[2]*loc2[2];
    double magProduct = getMagnitude(loc1) * getMagnitude(loc2);
    
    //acos() here returns the radian. The radian between two cities 
    //and radius of the earth gives curve length assuming earth is a uniform sphere
    return (acos(dotProduct/magProduct))*re;
}

std::string Routes::getDeparture() {
    return departure_.getID();
}
std::string Routes::getDestination() {
    return destination_.getID();
}

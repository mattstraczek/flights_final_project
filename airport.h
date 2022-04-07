#pragma once
#include <string>

class Airport {
    public:
        Airport();
        double getLatitude();
        double getLongitude();
        void setLatitude(double lat_);
        void setLongitude(double long_);
        
        void setID(std::string id);
        std::string getID();
    private:
        double latitude;
        double longitude;
        std::string ID;
        int index;
};
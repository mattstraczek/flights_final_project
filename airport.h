#pragma once
#include <string>

class Airport {
    public:
        /**
         * default constructor of the Airport class, initializes an Airport with ID "", latitude 0, and longitude 0
         **/
        Airport();

        /**
         * constructor of the Airport class, initializes an Airport with ID id, latitude lat, longitude longi, and
         *   index as the current airport map size
         **/
        Airport(std::string id, double lat, double longi, int index);

        /**
         * returns the latitude
         * @return the latitude of the Airport
         **/
        double getLatitude();

        /**
         * returns the longitude
         * @return the longitude of the Airport
         **/
        double getLongitude();

        /**
         * sets the latitude to a new value
         * @param lat_ is the new latitude
         **/
        void setLatitude(double lat_);

        /**
         * sets the longitude to a new value
         * @param long_ is the new longitude
         **/
        void setLongitude(double long_);

        /**
         * sets the airport ID to a new value
         * @param id is the new ID
         **/
        void setID(std::string id);

        /**
         * returns the airport ID
         * @return the airport ID of this Airport
         **/
        std::string getID();

        /**
         * returns the index
         * @return the index of this Airport
         **/
        int getIndex() const;

        /**
         * sets the index to a new value
         * @param idx is the new index
         **/
        void setIndex(int idx);

    private:
        double latitude; // the latitude of this Airport
        double longitude; // the longitude of this Airport
        std::string ID; // the airport ID of this Airport
        int index; // the index of this Airport
};

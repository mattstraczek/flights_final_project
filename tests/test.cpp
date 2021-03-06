#include "../cs225/catch/catch.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stack>
#include "../cs225/PNG.h"
#include "../airport.h"
#include "../routes.h"
#include "../parsing.h"
#include "../graph.h"

using namespace cs225;
using namespace std;

TEST_CASE("Extract airport single line", "[weight=10][part3]") {
  Parsing output;
  output.extractAirports("tests/single_airport.txt");
  std::unordered_map<std::string, Airport> airport_map = output.getAirportMap();
  Airport airport = airport_map["ORL"];
  REQUIRE(airport.getLatitude() == 28.5455);
  REQUIRE(airport.getLongitude() == -81.332901);
  REQUIRE(airport.getID() == "ORL");
}

TEST_CASE("Extract airport hard", "[weight=10][part4]") {
  Airport YFS = Airport("YFS", 61.76020050048828, -121.23699951171875, 0);
  Airport ITO = Airport("ITO", 19.721399307250977, -155.04800415039062, 1);
  Airport KAU = Airport("KAU", 63.127102, 23.051399, 2);
  Airport PIZ = Airport("PIZ", 69.73290253, -163.0050049, 3);
  Airport CVT = Airport("CVT", 52.3697013855, -1.4797199964499999, 4);
  Airport BTI = Airport("BTI", 70.1340026855, -143.582000732, 5);
  Airport AAL = Airport("AAL", 57.0927589138, 9.84924316406, 6);
  Airport LUR = Airport("LUR", 68.87509918, -166.1100006, 7);
  std::vector<Airport> airports;
  airports.push_back(YFS);
  airports.push_back(ITO);
  airports.push_back(KAU);
  airports.push_back(PIZ);
  airports.push_back(CVT);
  airports.push_back(BTI);
  airports.push_back(AAL);
  airports.push_back(LUR);
  Parsing output;
  output.extractAirports("tests/test_extract_hard.txt");
  std::unordered_map<std::string, Airport> airport_map = output.getAirportMap();
  std::unordered_map<std::string, Airport>::iterator it;
  unsigned i = 0;
  for (it = airport_map.begin(); it != airport_map.end(); it++) {
    if (i >= airports.size()) {
      REQUIRE(0 == 1);
      break;
    }
    Airport current = (*it).second;
    REQUIRE(airports[i].getID() == current.getID());
    REQUIRE(airports[i].getLatitude() == current.getLatitude());
    REQUIRE(airports[i].getLongitude() == current.getLongitude());
    i++;
  }
}

//Correct: "ADE", "ORD", etc
//Incorrect: "ade", "aDe", "a5d", "adee", "AD", "ADEE", "", "AD5", ADE, ORD
TEST_CASE("Airport ID parsing: Error-checking", "[weight=10][part5]") {
  Airport SFJ = Airport("SFJ", 67.0122218992, -50.7116031647, 0);
  Airport THU = Airport("THU", 76.5311965942, -68.7032012939, 1);
  std::vector<Airport> airports;
  airports.push_back(SFJ);
  airports.push_back(THU);
  Parsing output;
  output.extractAirports("tests/test_airport_id.txt");
  std::unordered_map<std::string, Airport> airport_map = output.getAirportMap();
  std::unordered_map<std::string, Airport>::iterator it;
  unsigned i = 0;
  for (it = airport_map.begin(); it != airport_map.end(); it++) {
    if (i >= airports.size()) {
      REQUIRE(0 == 1);
      break;
    }
    Airport current = (*it).second;
    REQUIRE(airports[i].getID() == current.getID());
    REQUIRE(airports[i].getLatitude() == current.getLatitude());
    REQUIRE(airports[i].getLongitude() == current.getLongitude());
    i++;
  }
}

//Correct: " 0.9..., 10.9..., -0.9..., -10.9...", [-90.0, 90]
//Incorrect: "Periods: -0.98.36, 0..983, 0.98.36, 0983, .983; Negatives: -876.5, 0-.908, 0.9-08, 0.9-0-8; No characters: 0.98a54, 19.54b3, p.492; In range: -92.398, 15923.8356"
TEST_CASE("Airport Latitude parsing: Error-checking", "[weight=10][part6]") {
  Airport TCN = Airport("TCN", 18.49720001220703, -97.4198989868164, 0);
  Airport CYA = Airport("CYA", 18.271099090576172, -73.78829956054688, 1);
  Airport BCA = Airport("BCA", 20.365299224853516, -74.5062026977539, 2);
  std::vector<Airport> airports;
  airports.push_back(TCN);
  airports.push_back(CYA);
  airports.push_back(BCA);
  Parsing output;
  output.extractAirports("tests/test_latitude.txt");
  std::unordered_map<std::string, Airport> airport_map = output.getAirportMap();
  std::unordered_map<std::string, Airport>::iterator it;
  unsigned i = 0;
  for (it = airport_map.begin(); it != airport_map.end(); it++) {
    if (i >= airports.size()) {
      REQUIRE(0 == 1);
      break;
    }
    Airport current = (*it).second;
    REQUIRE(airports[i].getID() == current.getID());
    REQUIRE(airports[i].getLatitude() == current.getLatitude());
    REQUIRE(airports[i].getLongitude() == current.getLongitude());
    i++;
  }
}

//Correct: "0.9..., 10.9..., 109.5..., -0.9..., -10.9..., -109.5...", [-180.0, 180]
//Incorrect: "Periods: -0.98.36, 0..983, 0.98.36, 0983, .983, 0983.937; Negatives: -876.5, 0-.908, 0.9-08, 0.9-0-8; No characters: 0.98a54, 19.54b3, p.492; In range: -192.398, 15923.8356"
TEST_CASE("Airport Longitude parsing: Error-checking", "[weight=10][part7]") {
  Airport NAW = Airport("NAW", 6.5199198722839355, 101.74299621582031, 0);
  Airport KGI = Airport("KGI", -30.789400100699996, 121.461997986, 1);
  Airport JHB = Airport("JHB", 1.64131, 103.669998, 2);
  std::vector<Airport> airports;
  airports.push_back(NAW);
  airports.push_back(KGI);
  airports.push_back(JHB);
  Parsing output;
  output.extractAirports("tests/test_longitude.txt");
  std::unordered_map<std::string, Airport> airport_map = output.getAirportMap();
  std::unordered_map<std::string, Airport>::iterator it;
  unsigned i = 0;
  for (it = airport_map.begin(); it != airport_map.end(); it++) {
    if (i >= airports.size()) {
      REQUIRE(0 == 1);
      break;
    }
    Airport current = (*it).second;
    REQUIRE(airports[i].getID() == current.getID());
    REQUIRE(airports[i].getLatitude() == current.getLatitude());
    REQUIRE(airports[i].getLongitude() == current.getLongitude());
    i++;
  }
}


//Correct: [ADE, ORD]; [MIA, SEA], etc
//Incorrect: [ord, mIa]; [s5a, adee]; [OR, MIAA]; [ , AD5]
TEST_CASE("Route ID parsing: Error-checking", "[weight=10][part8]") {
  Airport AER = Airport("AER", 43.449902, 39.9566, 0);
  Airport KZN = Airport("KZN", 55.606201171875, 49.278701782227, 1);
  Airport CEK = Airport("CEK", 55.305801, 61.5033, 2);
  Airport OVB = Airport("OVB", 55.012599945068, 82.650703430176, 3);
  std::vector<Routes> routes;
  Routes one = Routes(AER, KZN);
  Routes two = Routes(CEK, OVB);
  routes.push_back(one);
  routes.push_back(two);
  Parsing output;
  output.extractAirports("airports.txt");
  std::vector<Routes> extracted = output.extractRoutes("tests/test_extract_routes.txt");
  for (unsigned i = 0; i < extracted.size(); i++) {
    if (i >= routes.size()) {
      REQUIRE(0 == 1);
      break;
    }
    REQUIRE (extracted[i].getDeparture() == routes[i].getDeparture());
    REQUIRE (extracted[i].getDestination() == routes[i].getDestination());
  }
}

//Correct: 3416,"Orlando Executive Airport","Orlando","United States","ORL","KORL",28.5455,-81.332901,113,-5,"A","America/New_York","airport","OurAirports"
//Incorrect: 3426;"St Paul Island Airport","St. Paul Island"="United States","SNP"-"PASN",57.167301177978516+-170.22000122070312,63,-9,"A";"America/Anchorage","airport","OurAirports"
//Incorrectly formatted entries SKIPPED
TEST_CASE("Data formatting: Not comma seperated (airports.txt)", "[weight=10][part9]") {
  Airport GKA = Airport("GKA",-6.081689834590001, 145.391998291, 0);
  Airport LAE = Airport("LAE", -6.569803, 146.725977, 1);
  Airport SFJ = Airport("SFJ", 67.0122218992,-50.7116031647, 2);

  std::vector<Airport> airports;
  airports.push_back(GKA);
  airports.push_back(LAE);
  airports.push_back(SFJ);

  Parsing output;
  output.extractAirports("tests/test_airport_non_comma.txt");
  std::unordered_map<std::string, Airport> airport_map = output.getAirportMap();
  std::unordered_map<std::string, Airport>::iterator it;
  unsigned i = 0;
  for (it = airport_map.begin(); it != airport_map.end(); it++) {
    if (i >= airports.size()) {
      REQUIRE(0 == 1);
      break;
    }
    Airport current = (*it).second;
    REQUIRE(airports[i].getID() == current.getID());
    REQUIRE(airports[i].getLatitude() == current.getLatitude());
    REQUIRE(airports[i].getLongitude() == current.getLongitude());
    i++;
  }
}

//Correct: 2I,8359,AYP,2786,LIM,2789,,0,142
//Incorrect: 2I;8359,PEM-2808,CUZ+2812,/0,142
//Incorrectly formatted entries SKIPPED
TEST_CASE("Data formatting: Not comma seperated (routes.txt)", "[weight=10][part10]") {
  Airport AER = Airport("AER", 43.449902, 39.9566, 0);
  Airport KZN = Airport("KZN", 55.606201171875, 49.278701782227, 1);
  Airport CEK = Airport("CEK", 55.305801, 61.5033, 2);
  Airport OVB = Airport("OVB", 55.012599945068, 82.650703430176, 3);
  std::vector<Routes> routes;
  Routes one = Routes(AER, KZN);
  Routes two = Routes(CEK, OVB);
  routes.push_back(one);
  routes.push_back(two);
  Parsing output;
  output.extractAirports("airports.txt");
  std::vector<Routes> extracted = output.extractRoutes("tests/test_routes_non_comma.txt");
  for (unsigned i = 0; i < extracted.size(); i++) {
    if (i >= routes.size()) {
      REQUIRE(0 == 1);
      break;
    }
    REQUIRE (extracted[i].getDeparture() == routes[i].getDeparture());
    REQUIRE (extracted[i].getDestination() == routes[i].getDestination());
  }
}

//Correct: 3416,"Orlando Executive Airport","Orlando","United States","ORL","KORL",28.5455,-81.332901,113,-5,"A","America/New_York","airport","OurAirports"
//Incorrect: 3426,"St Paul Island Airport","St. Paul Island","United States","SNP","PASN",57.167301177978516,-170.22000122070312,63,-9,"A","America/Anchorage"
		   //3426,"St Paul Island Airport","St. Paul Island","United States"
		   // (blank)
//Incorrectly formatted entries SKIPPED
TEST_CASE("Data formatting: Deficient data entries (airports.txt)", "[weight=10][part11]") {
  Airport GKA = Airport("GKA",-6.081689834590001, 145.391998291, 0);
  Airport LAE = Airport("LAE", -6.569803, 146.725977, 1);
  Airport SFJ = Airport("SFJ", 67.0122218992,-50.7116031647, 2);

  std::vector<Airport> airports;
  airports.push_back(GKA);
  airports.push_back(LAE);
  airports.push_back(SFJ);

  Parsing output;
  output.extractAirports("tests/test_airport_missing.txt");
  std::unordered_map<std::string, Airport> airport_map = output.getAirportMap();
  std::unordered_map<std::string, Airport>::iterator it;
  unsigned i = 0;
  for (it = airport_map.begin(); it != airport_map.end(); it++) {
    if (i >= airports.size()) {
      REQUIRE(0 == 1);
      break;
    }
    Airport current = (*it).second;
    REQUIRE(airports[i].getID() == current.getID());
    REQUIRE(airports[i].getLatitude() == current.getLatitude());
    REQUIRE(airports[i].getLongitude() == current.getLongitude());
    i++;
  }
	
}

//Correct: 2I,8359,AYP,2786,LIM,2789,,0,142
//Incorrect: 2I,8359,PEM-2808,CUZ,2812
		   //2I,8359,PEM-2808
		   // (blank)
//Incorrectly formatted entries SKIPPED
TEST_CASE("Data formatting: Deficient data entries (routes.txt)", "[weight=10][part12]") {
  Airport AER = Airport("AER", 43.449902, 39.9566, 0);
  Airport KZN = Airport("KZN", 55.606201171875, 49.278701782227, 1);
  Airport CEK = Airport("CEK", 55.305801, 61.5033, 2);
  Airport OVB = Airport("OVB", 55.012599945068, 82.650703430176, 3);
  std::vector<Routes> routes;
  Routes one = Routes(AER, KZN);
  Routes two = Routes(CEK, OVB);
  routes.push_back(one);
  routes.push_back(two);
  Parsing output;
  output.extractAirports("airports.txt");
  std::vector<Routes> extracted = output.extractRoutes("tests/test_routes_missing.txt");
  for (unsigned i = 0; i < extracted.size(); i++) {
    if (i >= routes.size()) {
      REQUIRE(0 == 1);
      break;
    }
    REQUIRE (extracted[i].getDeparture() == routes[i].getDeparture());
    REQUIRE (extracted[i].getDestination() == routes[i].getDestination());
  }
	
}


TEST_CASE("testGeoMapSmall", "[weight=10][part13]") {
  std::cout << "------------------------------------------------------------" << std::endl;
  //small route (domestic)
  Parsing parse;
  parse.extractAirports("airports.txt");
  std::vector<Routes> list = parse.extractRoutes("routes.txt");
  std::unordered_map<std::string, Airport> airport_map = parse.getAirportMap();
  Graph graph(airport_map, list);

  airport_map = graph.getReducedMap();
  // std::cout << "Size of Routes: " << list.size() << std::endl;
  // std::cout << "Size of Reduced Routes: " << graph.getReducedRouteList().size() << std::endl;
  std::cout << "Creating small routes from Chicago (ORD) --> Los Angeles (LAX)" << std::endl;

  Airport a1 = airport_map.find("ORD")->second; 
  Airport a2 = airport_map.find("LAX")->second;

  Routes route(a1, a2);

  std::vector<Routes> routes;
  routes.push_back(route);

  graph.initgeoMap();

  graph.plotgeoMap(routes, "tests/geoMap_testSMALL.png");
  std::cout << "Please refer to the solution. ONLY 1 route should be printed" << std::endl;
}


TEST_CASE("testGeoMapMedium", "[weight=10][part14]") {
  std::cout << "------------------------------------------------------------" << std::endl;
  //midrange route (international)
  Parsing parse;
  parse.extractAirports("airports.txt");
  std::vector<Routes> list = parse.extractRoutes("routes.txt");
  std::unordered_map<std::string, Airport> airport_map = parse.getAirportMap();
  Graph graph(airport_map, list);

  airport_map = graph.getReducedMap();
  // std::cout << "Size of Routes: " << list.size() << std::endl;
  // std::cout << "Size of Reduced Routes: " << graph.getReducedRouteList().size() << std::endl;
  std::cout << "Creating small routes from USA Chicago (ORD) --> United Kingdom London Heathrow (LHR)" << std::endl;

  Airport a1 = airport_map.find("ORD")->second; 
  Airport a2 = airport_map.find("LHR")->second;

  Routes route(a1, a2);

  std::vector<Routes> routes;
  routes.push_back(route);

  graph.initgeoMap();

  graph.plotgeoMap(routes, "tests/geoMap_testMEDIUM.png");
  std::cout << "Please refer to the solution. ONLY 1 route should be printed" << std::endl;
}


TEST_CASE("testGeoMapLarge", "[weight=10][part15]") {
  std::cout << "------------------------------------------------------------" << std::endl;
  //long range route (international)
  Parsing parse;
  parse.extractAirports("airports.txt");
  std::vector<Routes> list = parse.extractRoutes("routes.txt");
  std::unordered_map<std::string, Airport> airport_map = parse.getAirportMap();
  Graph graph(airport_map, list);

  airport_map = graph.getReducedMap();
  // std::cout << "Size of Routes: " << list.size() << std::endl;
  // std::cout << "Size of Reduced Routes: " << graph.getReducedRouteList().size() << std::endl;
  std::cout << "Creating large routes from Spain Barcelona (BCN) --> Singapore Changi Airport (SIN)" << std::endl;

  Airport a1 = airport_map.find("BCN")->second; 
  Airport a2 = airport_map.find("SIN")->second;

  Routes route(a1, a2);

  std::vector<Routes> routes;
  routes.push_back(route);

  graph.initgeoMap();

  graph.plotgeoMap(routes, "tests/geoMap_testLarge.png");
  std::cout << "Please refer to the solution. ONLY 1 route should be printed" << std::endl;
  
}

TEST_CASE("testGeoMapLargeWrap", "[weight=10][part16]") {
  std::cout << "------------------------------------------------------------" << std::endl;
  //wrap long range route (international)
  Parsing parse;
  parse.extractAirports("airports.txt");
  std::vector<Routes> list = parse.extractRoutes("routes.txt");
  std::unordered_map<std::string, Airport> airport_map = parse.getAirportMap();
  Graph graph(airport_map, list);

  airport_map = graph.getReducedMap();
  // std::cout << "Size of Routes: " << list.size() << std::endl;
  // std::cout << "Size of Reduced Routes: " << graph.getReducedRouteList().size() << std::endl;
  std::cout << "Creating large wrap routes from USA Chicago (ORD) --> Japan Tokyo Narita Airport (NRT)" << std::endl;

  Airport a1 = airport_map.find("ORD")->second; 
  Airport a2 = airport_map.find("NRT")->second;

  Routes route(a1, a2);

  std::vector<Routes> routes;
  routes.push_back(route);

  graph.initgeoMap();

  graph.plotgeoMap(routes, "tests/geoMap_testLARGE_WRAP.png");
  std::cout << "Please refer to the solution. ONLY 1 route should be printed. This should wrap across the border on both ends. " << std::endl;
}

TEST_CASE("testMultipleRoutes", "[weight=10][part17]") {
  std::cout << "------------------------------------------------------------" << std::endl;
  Parsing parse;
  parse.extractAirports("airports.txt");
  std::vector<Routes> list = parse.extractRoutes("routes.txt");
  std::unordered_map<std::string, Airport> airport_map = parse.getAirportMap();
  Graph graph(airport_map, list);

  airport_map = graph.getReducedMap();
  // std::cout << "Size of Routes: " << list.size() << std::endl;
  // std::cout << "Size of Reduced Routes: " << graph.getReducedRouteList().size() << std::endl;
  std::cout << "Creating multiple routes" << std::endl;

  Airport a1 = airport_map.find("ORD")->second; 
  Airport a2 = airport_map.find("NRT")->second;
  Airport a3 = airport_map.find("BCN")->second; 
  Airport a4 = airport_map.find("SIN")->second;
  Airport a5 = airport_map.find("LHR")->second;

  Routes route1(a1, a2);
  Routes route2(a2, a3);
  Routes route3(a3, a4);
  Routes route4(a4, a5);

  std::vector<Routes> routes;
  routes.push_back(route1);
  routes.push_back(route2);
  routes.push_back(route3);
  routes.push_back(route4);

  graph.initgeoMap();

  graph.plotgeoMap(routes, "tests/geoMap_testCOMBINED.png");
  std::cout << "Please refer to the solution. 4 routes should be printed" << std::endl;
  
}

// If only one airport is read from the airport text file 
// Since only one node exists in the graph, a MST is unable to be built
TEST_CASE("testPrimsOneAriport", "[weight=10][part24]") {
  std::vector<std::pair<bool, std::string>> primsMST(std::string start_id);
  Parsing parse;
  parse.extractAirports("single_airport.txt");
  std::vector<Routes> list = parse.extractRoutes("routes.txt");
  std::unordered_map<std::string, Airport> airport_map = parse.getAirportMap();
  Graph graph(airport_map, list);
  //intialize a vector to store the MST 
  std::vector<std::pair<bool, std::string>> mst = graph.primsMST("ORL");
  REQUIRE (graph.getReducedMap().size() == 0);
  REQUIRE (mst.size() == 0);
}


// Make sure the starting Airport is apart of the graph
TEST_CASE("testPrimsConnectedStart", "[weight=10][part25]") {
  std::vector<std::pair<bool, std::string>> primsMST(std::string start_id);
  Parsing parse;
  parse.extractAirports("airports.txt");
  std::vector<Routes> list = parse.extractRoutes("tests/primsDirection.txt");
  std::unordered_map<std::string, Airport> airport_map = parse.getAirportMap();
  Graph graph(airport_map, list);
  //intialize a vector to store the MST 
  std::vector<std::pair<bool, std::string>> mst = graph.primsMST("ORD");
  std::cout << mst.size();
  REQUIRE (mst.size() == 0);
}

// std::cout << mst.size() << "\n";
// 	for(int i = 0; i < (int)mst.size(); i++){
// 		std::cout << mst[i].first <<  " ";
// 		std::cout << mst[i].second << "\n";
// 	}
 
// VALID MST:
// KZN -> AER
//  Check to see if valid routes are supplied to Prims, so that airplanes have an available route to a future airport
// 	Example: The Airport is currently at the airport "ORD", 
//  	A valid input route: AA,24,ORD,3830,ALO,5718,Y,0,ERD: the airport traversal is directed; and would proceed to "ALO"
//  	An invalid route: AA,24,ALO,5718,ORD,3830,Y,0,ERD: even though "ORD" is included in the route information, since "ORD" is not listed as
//  the start airport, "ALO" would not be visited in Prims, the above route would be needed in the routes.txt for "ALO" to be visited

TEST_CASE("testPrimsDirection", "[weight=10][part26]") {
	std::vector<std::pair<bool, std::string>> primsMST(std::string start_id);
	Parsing parse;
	parse.extractAirports("airports.txt");
	std::vector<Routes> list = parse.extractRoutes("tests/primsDirection.txt");
	std::unordered_map<std::string, Airport> airport_map = parse.getAirportMap();
	Graph graph(airport_map, list);
	//intialize a vector to store the MST 
	std::vector<std::pair<bool, std::string>> mst = graph.primsMST("KZN");
  std::vector<std::string> prev = graph.getPreviousVec();
	std::vector<std::string> sol = {"", "KZN", "", "", "", ""};

	for(int i = 0; i < (int)mst.size(); i++){
		if(mst[i].first == true){
      REQUIRE(prev[i] == sol[i]);
		}
	}
}

// Attempts Prims on a Small Graph
TEST_CASE("testPrimsSmallGraph", "[weight=10][part27]") {
	std::vector<std::pair<bool, std::string>> primsMST(std::string start_id);
	Parsing parse;
	parse.extractAirports("airports.txt");
	std::vector<Routes> list = parse.extractRoutes("tests/primsSmallGraph.txt");
	std::unordered_map<std::string, Airport> airport_map = parse.getAirportMap();
	Graph graph(airport_map, list);
	
	//intialize a vector to store the MST 
	std::vector<std::pair<bool, std::string>> mst = graph.primsMST("AER");
  std::vector<std::string> prev = graph.getPreviousVec();
	std::vector<std::string> sol = {"KZN", "", "AER", ""};
	int count = 0;
	for(int i = 0; i < (int)mst.size(); i++){
		if(mst[i].first == true){
			count++;
      REQUIRE(prev[i] == sol[i]);
		}
	}
	REQUIRE(count == 3);
 }

// In a connected graph, check to see if all airports are apart of the MST Tree
TEST_CASE("testPrimsSmallGraph2", "[weight=10][part28]") {
	std::vector<std::pair<bool, std::string>> primsMST(std::string start_id);
	Parsing parse;
	parse.extractAirports("airports.txt");
	std::vector<Routes> list = parse.extractRoutes("tests/primsSmallGraph2.txt");
	std::unordered_map<std::string, Airport> airport_map = parse.getAirportMap();
	Graph graph(airport_map, list);
	
	//intialize a vector to store the MST 
	std::vector<std::pair<bool, std::string>> mst = graph.primsMST("ZRH");
	std::vector<std::string> prev = graph.getPreviousVec();
	std::vector<std::string> sol = {"", "NCE", "HAM", "NCE", "ZRH", "BOD", "ZRH", "NCE"};
	
	int count = 0;
	for(int i = 0; i < (int)mst.size(); i++){
		if(mst[i].first == true){
			count++;
			REQUIRE(prev[i] == sol[i]);
 			}
	}
	REQUIRE(count == mst.size());
 }

// In a connected graph, check to see that proper MST is found when multiple spanning trees exist
TEST_CASE("testPrimsSmallGraph3", "[weight=10][part28]") {
	std::vector<std::pair<bool, std::string>> primsMST(std::string start_id);
	Parsing parse;
	parse.extractAirports("airports.txt");
	std::vector<Routes> list = parse.extractRoutes("tests/primsSmallGraph3.txt");
	std::unordered_map<std::string, Airport> airport_map = parse.getAirportMap();
	Graph graph(airport_map, list);
	
	//intialize a vector to store the MST 
	std::vector<std::pair<bool, std::string>> mst = graph.primsMST("ZRH");
	std::vector<std::string> prev = graph.getPreviousVec();
	std::vector<std::string> sol = {"", "NCE", "CGN", "NCE", "ZRH", "BRS", "ZRH", "ZRH"};
	
	int count = 0;
	for(int i = 0; i < (int)mst.size(); i++){
		if(mst[i].first == true){
			count++;
			REQUIRE(prev[i] == sol[i]);
 		}
	}
	REQUIRE(count == mst.size());
 }

TEST_CASE("testPrimsNULL", "[weight=10][part18]") {
  //should print a map that has No routes
  Parsing parse;
  parse.extractAirports("airports.txt");
  std::vector<Routes> list = parse.extractRoutes("routes.txt");
  std::unordered_map<std::string, Airport> airport_map = parse.getAirportMap();
  Graph graph(airport_map, list);
  airport_map = graph.getReducedMap();
  
  graph.initgeoMap();

  //Try to start Prims in fake airport called "ABC"
  graph.printPrimsMST("ABC", "geographic_map.png");

}

TEST_CASE("testBFSNULL", "[weight=10][part19]") {
  //should print a map that has No routes
  Parsing parse;
  parse.extractAirports("airports.txt");
  std::vector<Routes> list = parse.extractRoutes("routes.txt");
  std::unordered_map<std::string, Airport> airport_map = parse.getAirportMap();
  Graph graph(airport_map, list);
  airport_map = graph.getReducedMap();
  
  //Create fake airport
  Airport a1 = Airport();
  Airport a2("FAKE", 0, 0, -420);
  Airport Chicago = airport_map.find("ORD")->second;
  Airport a3("LAX", 0, 0, -420);
  Airport a4("BCN", 0, 0, -420);
  REQUIRE((graph.BFS(a1, Chicago)).size() == 0);
  REQUIRE((graph.BFS(Chicago, a2)).size() == 0);
  REQUIRE((graph.BFS(a1, a2)).size() == 0);
  REQUIRE((graph.BFS(Chicago, Chicago)).size() == 0);
  REQUIRE((graph.BFS(a3,a4)).size() == 0);
}

TEST_CASE("testBFS1", "[weight=10][part20]") {
  Parsing parse;
  parse.extractAirports("airports.txt");
  std::vector<Routes> list = parse.extractRoutes("routes.txt");
  std::unordered_map<std::string, Airport> airport_map = parse.getAirportMap();
  Graph graph(airport_map, list);
  airport_map = graph.getReducedMap();

  Airport a1 = airport_map.find("SBY")->second;
  Airport a2 = airport_map.find("CLT")->second;
  
  std::vector<std::string> bfs1 = graph.BFS(a1, a2);
  REQUIRE(bfs1.size() == 2);
  REQUIRE(bfs1[0] == "SBY");
  REQUIRE(bfs1[1] == "CLT");

  Routes route(a1, a2);

  std::vector<Routes> routes;
  routes.push_back(route);

  graph.initgeoMap();
  graph.plotgeoMap(routes, "tests/bfs1.png");
}

TEST_CASE("testBFS2", "[weight=10][part20]") {
  Parsing parse;
  parse.extractAirports("airports.txt");
  std::vector<Routes> list = parse.extractRoutes("routes.txt");
  std::unordered_map<std::string, Airport> airport_map = parse.getAirportMap();
  Graph graph(airport_map, list);
  airport_map = graph.getReducedMap();

  Airport a1 = airport_map.find("LAX")->second;
  Airport a2 = airport_map.find("GEA")->second;
  Airport a3 = airport_map.find("NOU")->second;
  REQUIRE((graph.BFS(a1,a2)).size() == 0);
  REQUIRE((graph.BFS(a1,a3)).size() > 0);
}


TEST_CASE("testBFS3", "[weight=10][part21]") {
  Parsing parse;
  parse.extractAirports("airports.txt");
  std::vector<Routes> list = parse.extractRoutes("routes.txt");
  std::unordered_map<std::string, Airport> airport_map = parse.getAirportMap();
  Graph graph(airport_map, list);
  airport_map = graph.getReducedMap();
  graph.initgeoMap();


  std::vector<std::string> bfsroute = graph.BFS(airport_map.find("ORD")->second, airport_map.find("NOU")->second);
  std::vector<Routes> shortest_route = graph.BFSRouteConvert(bfsroute);
	std::cout << "Passed BFS";
  graph.plotgeoMap(shortest_route, "tests/bfs3.png", 0);

  //Test potential alternative route;
  Airport lax = airport_map.find("LAX")->second;
  Airport nou = airport_map.find("NOU")->second;
  Airport bne = airport_map.find("BNE")->second;
  Airport ord = airport_map.find("ORD")->second;
  
  Routes r1(ord, lax);
  Routes r2(lax, bne);
  Routes r3(bne, nou);

  std::vector<Routes> routes;

  routes.push_back(r1);
  routes.push_back(r2);
  routes.push_back(r3);

  graph.initgeoMap();
  graph.plotgeoMap(routes, "tests/bfs3.png");
  
  //compare alternative route distance with shortest path determined through BFS
  REQUIRE(shortest_route.size() <= routes.size());
  std::cout << "Passed vector creation\n";
  int index = ord.getIndex();
  std::vector<Airport> airports = graph.getDestinations(index);
  std::cout << "Passed getDestinations()\n";
  for (unsigned i = 0; i < airports.size(); i++) {
    REQUIRE("NOU" != airports[i].getID());
  }
}


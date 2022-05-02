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


bool testFiles(string f1, string f2) {
	string line1;
	string line2;
  	ifstream file1(f1);
	std::vector<string> lines1;
	std::vector<string> lines2;

  	if(file1.is_open()) {
      while(getline(file1, line1)) {
        std::cout << line1 << std::endl;
		lines1.push_back(line1);
	  }
	}
	file1.close();
	ifstream file2(f2);

	std::cout << "hello" << std::endl;
	if(file2.is_open()) {
		while(getline(file2, line2)) {
			std::cout << line2 << std::endl;
			lines2.push_back(line2);
	  	}
	}
	file2.close();

	for(size_t i = 0; i < lines1.size(); i++) {
		if(lines1[i] != lines2[i]) {
			return false;
		}
	}
	return true;
}

// TEST_CASE("Parse airport data", "[weight=10][part1]") {
// 	Parsing parse_test;

// 	parse_test.extractAirports("test_airport.txt");
// 	parse_test.writeAirports("test_airport_returning.txt");

// 	REQUIRE(testFiles("/workspaces/CS 225/junryuf2/lboelke2-aosepek2-junryuf2-mstrac4/tests/test_airport_soln.txt", "workspaces/CS 225/junryuf2/lboelke2-aosepek2-junryuf2-mstrac4/tests/test_airport_returning.txt"));
// }

// TEST_CASE("Adjacency matrix construction", "[weight=10][part2]") {
// 	std::unordered_map<std::string, Airport> airport_map;
// 	std::vector<Routes> route_list;

// 	//Creating airport map
// 	Airport ORD("ORD", 41.9786, -87.9048, 0);
// 	Airport MIA("MIA", 25.7931, -80.2906, 1);
// 	Airport SEA("SEA", 47.449001, -122.308998, 2);

// 	airport_map[ORD.getID()] = ORD;
// 	airport_map[MIA.getID()] = MIA;
// 	airport_map[SEA.getID()] = SEA;

// 	//Creating route list
// 	Routes ORDMIA(ORD, MIA);
// 	Routes MIASEA(MIA, SEA);
// 	Routes SEAORD(SEA, ORD);

// 	route_list.push_back(ORDMIA);
// 	route_list.push_back(MIASEA);
// 	route_list.push_back(SEAORD);

// 	//Creating graph
// 	Graph graph(airport_map, route_list);
// 	graph.printRouteMatrix();

// 	//Solution (Expected) Matrix
// 	//            ORD      MIA       SEA       
// 	// ORD       -1        1932      -1        
// 	// MIA       -1        -1        4384      
// 	// SEA       2764      -1        -1       

// 	//Creating solution graph
// 	std::vector<std::vector<int> >& route_matrix = graph.getRouteMatrix();
// 	std::vector<std::vector<int> > solution;

// 	std::vector<int> SEA_;
// 	SEA_.push_back(-1);
// 	SEA_.push_back(1932);
// 	SEA_.push_back(-1);

// 	std::vector<int> ORD_;
// 	ORD_.push_back(-1);
// 	ORD_.push_back(-1);
// 	ORD_.push_back(4384);

// 	std::vector<int> MIA_;
// 	MIA_.push_back(2764);
// 	MIA_.push_back(-1);
// 	MIA_.push_back(-1);

// 	solution.push_back(SEA_);
// 	solution.push_back(ORD_);
// 	solution.push_back(MIA_);

// 	//Test that resultant matrix matches solution
// 	REQUIRE(solution == route_matrix);
// }

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

TEST_CASE("testHandleNULLAirport_1", "[weight=10][part18]") {
  //case where the airport added is not appropriate 
}

TEST_CASE("testHandleNULLAirport_2", "[weight=10][part19]") {
  //case where the route does not actually exist commercially
  
}
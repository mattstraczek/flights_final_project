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

TEST_CASE("Parse airport data", "[weight=10][part1]") {
	Parsing parse_test;

	parse_test.extractAirports("test_airport.txt");
	parse_test.writeAirports("test_airport_returning.txt");

	REQUIRE(testFiles("/workspaces/CS 225/junryuf2/lboelke2-aosepek2-junryuf2-mstrac4/tests/test_airport_soln.txt", "workspaces/CS 225/junryuf2/lboelke2-aosepek2-junryuf2-mstrac4/tests/test_airport_returning.txt"));
}

TEST_CASE("Adjacency matrix construction", "[weight=10][part2]") {
	std::unordered_map<std::string, Airport> airport_map;
	std::vector<Routes> route_list;

	//Creating airport map
	Airport ORD("ORD", 41.9786, -87.9048, 0);
	Airport MIA("MIA", 25.79319953918457, -80.29060363769531, 1);
	Airport SEA("SEA", 47.449001, -122.308998, 2);

	airport_map[ORD.getID()] = ORD;
	airport_map[MIA.getID()] = MIA;
	airport_map[SEA.getID()] = SEA;

	//Creating route list
	Routes ORDMIA(ORD, MIA);
	Routes MIASEA(MIA, SEA);
	Routes SEAORD(SEA, ORD);

	route_list.push_back(ORDMIA);
	route_list.push_back(MIASEA);
	route_list.push_back(SEAORD);

	//Creating graph
	Graph graph(airport_map, route_list);
	graph.printRouteMatrix();

	//Solution (Expected) Matrix
	//            SEA      ORD       MIA       
	// SEA       -1        1932      -1        
	// ORD       -1        -1        4384      
	// MIA       2764      -1        -1       

	//Creating solution graph
	std::vector<std::vector<int> >& route_matrix = graph.getRouteMatrix();
	std::vector<std::vector<int> > solution;

	std::vector<int> SEA_;
	SEA_.push_back(-1);
	SEA_.push_back(1932);
	SEA_.push_back(-1);

	std::vector<int> ORD_;
	ORD_.push_back(-1);
	ORD_.push_back(-1);
	ORD_.push_back(4384);

	std::vector<int> MIA_;
	MIA_.push_back(2764);
	MIA_.push_back(-1);
	MIA_.push_back(-1);

	solution.push_back(SEA_);
	solution.push_back(ORD_);
	solution.push_back(MIA_);

	//Test that resultant matrix matches solution
	REQUIRE(solution == route_matrix);
}

TEST_CASE("Extract airport single line", "[weight=10][part3]") {
  Parsing output;
  output.extractAirports("single_airport.txt");
  output.writeAirports("single_airport_returning.txt");
  std::unordered_map<std::string, Airport> airport_map = output.getAirportMap();
  std::string id = "ORL";
  Airport airport = airport_map[id];
  std::cout << (airport.getLatitude()) << std::endl;
/*  REQUIRE(airport.getLatitude() == 68.87509918);
  REQUIRE(airport.getLongitude() == -166.1100006);
  REQUIRE(airport.getID() == "ORL");*/
}

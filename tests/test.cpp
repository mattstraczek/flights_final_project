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

TEST_CASE("parse airport data", "[weight=10][part1]")
{
	Parsing parse_test;

	parse_test.extractAirports("test_airport.txt");
	parse_test.writeAirports("test_airport_returning.txt");

	REQUIRE(testFiles("/workspaces/CS 225/junryuf2/lboelke2-aosepek2-junryuf2-mstrac4/tests/test_airport_soln.txt", "workspaces/CS 225/junryuf2/lboelke2-aosepek2-junryuf2-mstrac4/tests/test_airport_returning.txt"));
}
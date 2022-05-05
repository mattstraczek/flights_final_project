# lboelke2-aosepek2-junryuf2-mstrac4
The final project git repo for team the four amigos
- Project Contributors: Luke Boelke, Junryu Fu, Matt Straczek, Andrew Osepek
# CS 225 Spring 2022 Final Project
## Overview
- The main goal of our final project is to operate an airline as efficiently as possible. We will use the airport and route data from openflights.org and store this data in an adjacency list, which can then be represented by a graph. The vertices of this graph will be the airports and the edges will be the flight paths from one airport to another. The specific problem we are trying to solve is to minimize the amount of service routes as much as possible, while still being able to connect all of the airports in a region.
## Building Project
- Clone Repository from https://github-dev.cs.illinois.edu/cs225-sp22/lboelke2-aosepek2-junryuf2-mstrac4.git
## DataSet 
- https://openflights.org/data.html
- Airports: [Airpot Data](airports.txt)
- Routes: [Routes Data](routes.txt)
- - - -
## Algorithms and Parsing
- BFS
    - Find the least amount of transfers between two airports
    - Files:
    - [graph.h](graph.h)
    - [graph.cpp](graph.cpp)
- Prims
    - Find a MST of all airports globally
    - Files:
    - [graph.h](graph.h)
    - [graph.cpp](graph.cpp)
- Geographical Output
    - Create an image that highlights the routes included in Prims and BFS
    - Files:
    - [graph.h](graph.h)
    - [graph.cpp](graph.cpp)
- Parses the data from Openflights
    - Files:
    - [parsing.h](parsing.h)
    - [parsing.cpp](parsing.cpp)
## Running Instructions
- Type `make out` to create the executable file 
- Then type, `./out` to run the executable 
- After runnning the executable, the terminal will prompt the user which algorithm or graphical output program they will like to run
- Type `a` for Prims
    - When prompted enter the starting airport ID for Prim's algorithm (ex: ORD, LAX)
    - Saves a list of routes included in the MST to the file text_output.txt 
    - Saves a visualize image of the MST output to the file geographic_map.png
- Type `b` for BFS
    - When prompted enter a start airport ID, then enter a destination airport ID when asked (ex: ORD, LAX) 
    - Saves an image of the BFS traversal to a png file geographic_map.png
    - Saves a list of airports in the order they were visited to a text file, text_output.png 
- Type `c` for plotting a route between two airports
    - When prompted enter a start airport ID, then enter a destination airport ID when asked (ex: ORD, LAX)
    - Save an image to a png file labelled geographic_map.png, which highlights visually a route between the start and a destination airport
- Type `d` to quit
    - Quits the program 
- Any invalid entry
    - The user will be alerted of their invalid entry and the program will sequentially exist

## Testing Instructions
- Type `make test` 
- Then, type `./test` which will run the test file executable 
- The written code for the test cases can be found in file test.cpp under the tests directory in our main branch. Associated text files used for various test cases can also be found within the tests directory. 
- Overview of Test Cases:
    - Parsing Text File:
        - Ensures data being read from text file is formatted correctly or else it is not included in our data
    - Prims:
        - Check to see if the starting airport is inlcuded in the graph and connected to at least one other airport
        - If an invalid route structure is passed to Prims, associated airports would not be included in the MST
        - Check to see that the minimal edge (route) is selected when constructing the MST
    - BFS:
        - Checks to see if start node is equal to end node
        - Checks if the start node and end node are connected 
        - Checks adjacent airports, whether unconnected graphs are handled
    - GeoGraphical OutPut:
        - Outputs a geoMap image into the tests directory, which can be compared to the associated geoMap_SOLN also within the tests directory
        - example:
        -  Outputed file from test case: geoMap_testCOMBINED.png 
        - Solution file screenshotted from Google Maps: geoMap_testCOMBINED_SOLN.png
            - Compare the visualize similarities between the outputted png file to the solution png file
## Presentation
- Final Presentation Link: https://drive.google.com/file/d/14iz0k2oXFrMGJCOiCea34snWzdpGwRrK/view?usp=drivesdk
- Written Report Link: *******

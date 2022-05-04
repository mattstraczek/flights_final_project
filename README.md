# lboelke2-aosepek2-junryuf2-mstrac4
The final project git repo for team the four amigos
# CS 225 Spring 2021 Final Project

## Overview
- The main goal of our final project is to operate an airline as efficiently as possible. We will use the airport and route data from openflights.org and store this data in an adjacency list, which can then be represented by a graph. The vertices of this graph will be the airports and the edges will be the flight paths from one airport to another. The specific problem we are trying to solve is to minimize the amount of service routes as much as possible, while still being able to connect all of the airports in a region.
## Building Project
- Clone Repository from https://github-dev.cs.illinois.edu/cs225-sp22/lboelke2-aosepek2-junryuf2-mstrac4.git
## DataSet 
- https://openflights.org/data.html
- Airports: [a relative link](airports.txt)
- Routes: [a relative link](routes.txt)
- - - -
## Testing Instructions
- Type `make test` 
- Then, type `./test` which will run the test file executable 
- The written code for the test cases can be found in the file test.cpp under the tests directory in our main branch. Associated text files used for various test cases can also be found within the tests directory. 
- Test Cases:
    - Parsing Text File:
        - Ensures data being read from text file is formatted correctly or else it is not included in our data
    - Prims:
        - Check to see if the starting airport is inlcuded in the graph and connected to at least one other airport
        - If invalid Route structures are passed to Prims, associated airports would not be included in the MST
    - BFS:
        - Checks to see if start node is equal to end node
        
    - GeoGraphical OutPut:


## Running Instructions
- Type `make out` to create the executable file 
- Then type, `./out/` to run the executable 
- After runnning the executable, the terminal will prompt the user which algorithm or graphical output program they will like to run
- Type `a` for Prims
    - Then enter the starting airport ID for Prim's algorithm (ex: ORD, LAX)
    - Saves a list of routes included in the MST to the file text_output.txt 
    - Saves a visualize image of the MST output to the file geographic_map.png
- Type `b` for BFS
    - When prompted enter a start airport ID, then enter a destination airport ID when asked(ex: ORD, LAX) 
    - Saves an image of the BFS traversal to a png file geographic_map.png
    - Saves a list of airports in the order they were visited to a text file, text_output.png 
- Type `c` for plotting a route between two airports
    - When prompted enter a start airport ID, then enter a destination airport ID when asked (ex: ORD, LAX)
    - Save an image to the png file geographic_map.png,  highlighting the visual route between a start and a destination airport
- Type `d` to quit
    - Quits the program
- Any invalide entry
    - The user will be alerted of their invalid entry and the program will sequentally 

## Algorithms
- BFS
    - Find the shortest path between two airports
- Prims
    - Find a MST of all airports globally
- Geographical Output
    - Create an image that highlights the routes included Prims and BFS

## Presentation
- ***ADD link to presentation video

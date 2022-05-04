# lboelke2-aosepek2-junryuf2-mstrac4
The final project git repo for team the four amigos
# CS 225 Fall 2020 Final Project

## Overview

## Building Project
- Clone Repository from https://github-dev.cs.illinois.edu/cs225-sp22/lboelke2-aosepek2-junryuf2-mstrac4.git

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
## Breadth First Search (BFS)

## Presentation
- ***ADD link to presentation video
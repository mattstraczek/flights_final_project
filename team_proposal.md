# Team Proposal (lboelke2-aosepek2-junryuf2-mstrac4)
1. **Leading Question**
+ The main goal of our final project is to operate an airline as efficiently as possible. We will use the airport and route data from openflights.org and store this data in an adjacency matrix, which can then be represented by a graph. The vertices of this graph will be the airports and the edges will be the flight paths from one airport to another. The specific problem we are trying to solve is to minimize the amount of service routes as much as possible, while still being able to connect all of the airports in a region. We will be focusing on US airports, but our data structure would be able to store all the airports in the world if necessary.

2. **Data Acquisition and Processing**
+ **Data format** (one paragraph): We will be using airline data from the open flights website (https://openflights.org/data.html). The format the data will be in originally is a dat file, which we will then convert to a csv file to make it easier to read from. There are two data sets we will be using, the airport data and the route data. The airport data contains the airport name, the city it is in, the country it is in, the abbreviation of the name, geographical coordinates, etc. The route data contains the airline, the airline ID, the source and destination airports, as well as number of stops. We plan to only use a subset of the data, as the data includes all airports in the world, but we are only using the airports in the US. This will be done during the data correction process. The size of the airport dataset is over 10,000 airports, 1,512 of which are in the US. The size of the route dataset is over 60,000 routes globally, and is around 2 MB.
+ **Data correction** (one or two paragraphs): The data will be converted to a csv file, where we will read the information of each entry of the data set. For the airport data, each entry is composed of specific identifiers of the airport that are comma separated. Similarly, the route's dataset follows a similar organization, where the route's information is comma separated. Each entry of the datasets are organized on new lines of the csv file. With this organization, adding data to the graph will be simple. If a data entry is missing information, two commas will be adjacent to one another. Data entries with missing information will still be considered if they contain information regarding the airport’s name and geographical coordinates. However, if data entries are included in the dataset that miss these critical identifiers the data entry will not be added to the graph. 
+ **Data Storage** (one or two paragraphs): The edges of our graph will be the flight paths between two airports. These edges will be directed because the flights from one airport to another, say LAX to ODR, is different from the flight in the other direction, ODR to LAX. These will be two different cells in the adjacency matrix. The weights of these edges will be the geographical distances between the airports, in miles. Because the locations of the airports are given in latitude and longitude coordinates, we will convert these distances to miles, using the fact that one degree longitude is 54.6 miles and one degree latitude is 69 miles. These weights will be the values stored in the cells of the adjacency matrix. Due to the large amount of edges (flights) at every airport (vertex), we will use an adjacency matrix to represent this graph of flights. The adjacency matrix would be implemented using a 2-dimensional vector. The total storage costs for this adjacency matrix would be O(A^2), where a is the number of airports.

3. **Graph Algorithms**
+ **Prim’s algorithm**:
+ Function Inputs: The input for this function would be the entire adjacency matrix - represented graph.
+ Function Outputs: The expected output is still unknown, however it is expected to produce a minimum spanning tree between all of the airlines. An adjacency list can be used to store the output, since the number of edges will drastically decrease once a minimum spanning tree is found.
+ Function Efficiency: Time complexity: O(A^2), where A is the airport nodes.
+ **Graphic output of graph (Project onto map based on data):**
+ Function Inputs: We will input all The input for this function would be the adjacency list output of running Prim’s algorithm.
+ Function Outputs: outputs an image (map) with airports nodes and vertices connecting different routes, and for the output of Prim’s algorithm, it will display it differently, for example, in red. 
+ Function Efficiency: Time complexity: O(A + F), where A is the airport nodes, and F is the flights connecting two airports. 
+ **BFS Traversal**:
+ Function Inputs: The input for this function would be the entire adjacency matrix - represented graph and a starting node (airport).
+ Function Outputs: The expected output is expected to produce a Breadth-first Search.
+ Function Efficiency: Time complexity: O(A + F), where A is the airport nodes, and F is the flights connecting two airports. This is desired over DFS since the time complexity of that traversal on an adjacency matrix is O(A^2).

4. **Timeline**
+ Complete lab contract and lab proposal and submit (Friday of week 1)
+ Find the best way to parse through the data, check for errors and eliminate these errors so that the data is able to be used in our data structure, start constructing constructor and destructor for the data structure (Week 2)
+ Decide and write pseudocode for graph algorithm 1 (classes, variables, functions) (Week 3)
+ Decide and write pseudocode for graph algorithm 2 (classes, variables, functions) (Week 4)
+ Completion of graph algorithm 1 and 2 and debug (Week 5)
+ Start drafting final report and finalize presentation(Week 6)
+ Make sure everything works as intended and deliverables are done, and submit the final product (Week 7)


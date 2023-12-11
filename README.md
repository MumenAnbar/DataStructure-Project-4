# DataStructure-Project-4
## Overview
This C project implements Dijkstra's Algorithm and Breadth-First Search (BFS) to find the shortest path between two cities in a given graph. It constructs the graph using an adjacency list and employs a priority queue based on a segment tree, utilizing pointers for efficient traversal and manipulation.

## Getting Started

### Features
- Dijkstra's Algorithm: Computes the shortest path between two cities using weighted edges.
- BFS (Breadth-First Search): Finds the shortest path in an unweighted graph.
- Adjacency List: Efficiently constructs the graph representation for storing city connections.
- Priority Queue with Segment Tree: Implements a priority queue using the segment tree data structure for optimal path calculation.
- Pointers: Utilizes pointers for memory management and efficient traversal of the graph and queue.

### Prerequisites
- C compiler.
- cities.txt file.

### Usage
1.  Modify cities.txt to represent the cities and connections in the graph.
2.  Run the executable: ./main
3.  Follow the prompts to input the source and destination cities.
4.  View the shortest path output on the console.

### Segment Tree Implementation
- The segment tree implementation used here supports operations like update and query efficiently.

## Example
``` plaintext
Please Choose One Of The Following:
1- Load Cities From The File.
2- Enter Source City.
3- Enter Destination City.
4- Exit.

1
DONE!

Please Choose One Of The Following:
1- Load Cities From The File.
2- Enter Source City.
3- Enter Destination City.
4- Exit.

2
Haifa

Please Choose One Of The Following:
1- Load Cities From The File.
2- Enter Source City.
3- Enter Destination City.
4- Exit.

3
Hebron
For Dijkistra:
  The Cost To Move From The Given Cities = 356
  The Path Is: Hebron <- Bethlehem <- Ramallah <- Jericho <- Tubas <- Jenin <- Haifa
For BFS:
  The Cost To Move From The Given Cities = 6
  The Path Is: Hebron <- Bethlehem <- Ramallah <- Jericho <- Nablus <- Jenin <- Haifa

Please Choose One Of The Following:
1- Load Cities From The File.
2- Enter Source City.
3- Enter Destination City.
4- Exit.

4
All Answers Are Saved To (output.txt)

/*
Implement a Hex player
C++ for C Programmers: Part B
Week 2
Rishabh Bhattacharya
Jul 29th, 2023

This program implements a single player Hex game against the computer.


Program description: 
*/
#include<iostream>
#include<cstdlib>

#include "include/Graph.h"
#include "include/ShortestPath.h"


int main(int argc, char **argv) {
    srand(time(0));     // Output is provided with srand(7);
    
    Graph graph(50, 0.2, 1, 10, false);         // Create graph
    ShortestPath shortest_path(1, 27, graph);   // Initialize shortest path
    
    return 0;
}
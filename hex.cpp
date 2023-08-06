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
// #include "include/ShortestPath.h"


int main(int argc, char **argv)
{
    int board_size = 5;
    if (argc > 1)
    {
        try
        {
            board_size = std::stoi(argv[1]);
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error: Invalid board size argument! Should be an integer, given '" << argv[1] << "'.\n";
            return 1;
        }
    }

    Graph graph(board_size);
    graph.playGame();
    return 0;
}
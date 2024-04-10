/*
Implement a Hex player
C++ for C Programmers: Part B
Week 2
Rishabh Bhattacharya
Jul 29th, 2023

This program implements a single player Hex game against the computer.


Program description:
*/

#include <iostream>

#include "include/board.h"

int main(int argc, char **argv)
{
    int boardSize = 4;
    if (argc > 1)
    {
        try
        {
            boardSize = std::stoi(argv[1]);
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error: Invalid board size argument! Should be an integer, given '" << argv[1] << "'.\n";
            std::cout << "Enter board size: ";
            cin >> boardSize;
        }
    }

    // int HumanPlayer::humanCount = 0;
    // TODO: Choose first player
    // TODO: Show human orientation during human move
    // TODO: Send NTRIALS as program input parameter
    vector<IPlayer *> players = {new CompPlayer("Computer"), new HumanPlayer("Human")};
    
    Board hexBoard(boardSize, players);
    hexBoard.playGame();

    for (auto player : players)
        player = (delete player, nullptr);
    
    return 0;
}
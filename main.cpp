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
#include <vector>
#include <memory>

#include "include/player/comp_player.hpp"
#include "include/player/human_player.hpp"
#include "include/computer_logic/monte_carlo.hpp"
#include "include/board/board.hpp"

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
            std::cin >> boardSize;
        }
    }

    // int HumanPlayer::humanCount = 0;
    // TODO: Choose first player
    // TODO: Show human orientation during human move

    std::cout << "Enter no. of trials for the Monte Carlo simulation: ";
    int nTrials;
    std::cin >> nTrials;
    std::shared_ptr<IComputerLogic> computerLogic = std::make_shared<MonteCarlo>(nTrials);
    std::shared_ptr<IPlayer> compPlayer = std::make_shared<CompPlayer>("Monte Carlo Computer", computerLogic);

    std::cout<< "Enter name of human player: ";
    std::string humanName = "Rishabh";
    std::cin >> humanName;
    std::shared_ptr<IPlayer> humanPlayer = std::make_shared<HumanPlayer>(humanName);

    std::cout << compPlayer->GetPlayerName() << " vs. " << humanPlayer->GetPlayerName() << '\n';
    std::vector<std::shared_ptr<IPlayer>> players = {compPlayer, humanPlayer};
    
    Board hexBoard(boardSize, players);
    hexBoard.playGame();
    
    return 0;
}
#include <iostream>
#include <vector>
#include <memory>

#include "include/player/Player.hpp"
#include "include/player/comp_player.hpp"
#include "include/player/human_player.hpp"
#include "include/computer_logic/monte_carlo.hpp"
#include "include/board/board.hpp"
#include "include/enums.hpp"
#include "include/player/player_factory.hpp"

int getBoardSize(int argc, char **argv)
{   
    int defaultBoardSize = 4, newBoardSize = -1;
    
    if (argc > 1)
    {
        try
        {
            newBoardSize = std::stoi(argv[1]);
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error: Invalid board size argument! Should be an integer, given '" << argv[1] << "'.\n";
            std::cout << "Enter board size: ";
            std::cin >> newBoardSize;
        }
    }
    
    return newBoardSize > 0 ? newBoardSize : defaultBoardSize;
}

vspPlayer decidePlayerOrder(spPlayer player1, spPlayer player2)
{
    int firstPlayer;
    vspPlayer players(2);
    do {
        std::cout << "Who should go first? Enter 1 for "<< player1->getName() << " and 2 for " << player2->getName() << ": ";
        std::cin >> firstPlayer;

        if (firstPlayer == 1)
        {
            std::cout << player1->getName() << " goes first.\n";
            players = {player1, player2};
        }
        else if (firstPlayer == 2) 
        {
            std::cout << player2->getName() << " goes first.\n";
            players = {player2, player1};
        }
        else
        {
            std::cout << "Invalid input. Please try again and enter 1 or 2.\n";
        }
    }while (firstPlayer != 1 && firstPlayer != 2);

    return players;
}

int main(int argc, char **argv)
{
    int boardSize = getBoardSize(argc, argv);

    spPlayer player1 = PlayerFactory::createPlayer("Tony Stark");
    spPlayer player2 = PlayerFactory::createPlayer(ComputerLogic::MONTE_CARLO);
    vspPlayer players = decidePlayerOrder(player1, player2);
    
    Board hexBoard(boardSize, players);
    hexBoard.playGame();
    
    return 0;
}
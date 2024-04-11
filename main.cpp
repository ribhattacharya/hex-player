#include <iostream>
#include <vector>
#include <memory>

#include "include/player/comp_player.hpp"
#include "include/player/human_player.hpp"
#include "include/computer_logic/monte_carlo.hpp"
#include "include/board/board.hpp"
#include "include/enums.hpp"
#include "include/player/player_factory.hpp"

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


    std::shared_ptr<IPlayer> compPlayer = PlayerFactory::CreateCompPlayer(ComputerLogic::MONTE_CARLO);
    std::shared_ptr<IPlayer> humanPlayer = PlayerFactory::CreateHumanPlayer("Tony Stark");
    std::vector<std::shared_ptr<IPlayer>> players(2);

    std::cout << "Who should go first? Enter 1 for computer and 2 for human: ";
    int firstPlayer;
    std::cin >> firstPlayer;

    if (firstPlayer == 1)
    {
        std::cout << "Computer goes first.\n";
        players = {compPlayer, humanPlayer};
    }
    else
    {
        std::cout << "Human goes first.\n";
        players = {humanPlayer, compPlayer};
    }
    
    Board hexBoard(boardSize, players);
    hexBoard.playGame();
    
    return 0;
}
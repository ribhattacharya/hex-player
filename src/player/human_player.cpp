#include <iostream>
#include <string>

#include "../../include/player/human_player.hpp"

// using std::cin;
// using std::cout;
// using std::string;

HumanPlayer::HumanPlayer(std::string name, PlayerType type) : Player(name, type) {}

Pair HumanPlayer::decideNextMove(const Graph &g) const
{
    int row = 0, col = 0;
    std::cout << "Enter row: ";
    std::cin >> row;
    std::cout << "Enter column: ";
    std::cin >> col;

    return std::make_pair(row, col);
}
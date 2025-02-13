#include "player/HumanPlayer.hpp"

#include <iostream>
#include <utility>

HumanPlayer::HumanPlayer(std::string name, PlayerIDEnum playerID)
    : Player(name, playerID) {
}

IntPair HumanPlayer::getMove(const Board& board) const {
    IntPair move = std::make_pair(-1, -1);

    std::cout << "Enter row: ";
    std::cin >> move.first;
    std::cout << "Enter column: ";
    std::cin >> move.second;

    return move;
}
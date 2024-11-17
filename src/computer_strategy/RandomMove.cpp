#include "../../include/computer_strategy/RandomMove.hpp"

#include <random>
#include <utility>

IntPair RandomMove::calculateMove(const Board& board, PlayerIDEnum playerId) {
    std::random_device rd;
    std::mt19937 gen(rd());

    // Define the range for the distribution
    std::uniform_int_distribution<> dis(0, board.getSize() - 1);

    // Generate a single random integer
    int row = dis(gen), col = dis(gen);

    return std::make_pair(row, col);
}
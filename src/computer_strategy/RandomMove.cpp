#include "computer_strategy/RandomMove.hpp"

#include <random>

IntPair RandomMove::_calculateMove(const Board& board,
                                   PlayerIDEnum curPlayerId) const {
    std::random_device rd;
    std::mt19937 gen(rd());

    // Get all valid moves and return a random one
    VectIntPair validMoves = _getAvailableMoves(board);

    if (validMoves.empty()) {
        // Should not happen unless board is full
        return {-1, -1};
    }

    std::uniform_int_distribution<> dis(0, validMoves.size() - 1);
    return validMoves[dis(gen)];
}
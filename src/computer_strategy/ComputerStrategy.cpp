#include "computer_strategy/ComputerStrategy.hpp"
#include "Utility.hpp"

#include <chrono>
#include <iostream>

IntPair ComputerStrategy::getMove(const Board& board,
                                  PlayerIDEnum curPlayerId) const {
    auto start = std::chrono::high_resolution_clock::now();

    IntPair move = _calculateMove(board, curPlayerId);

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed =
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << DIM << "🤖 AI thinking time: " << elapsed.count() << "ms"
              << RESET << std::endl;
    return move;
}

VectIntPair ComputerStrategy::_getAvailableMoves(const Board& board) const {
    VectIntPair availableMoves;
    for (int i = 0; i < board.getSize(); i++) {
        for (int j = 0; j < board.getSize(); j++) {
            if (board.isValidMove({i, j})) {
                availableMoves.push_back({i, j});
            }
        }
    }
    return availableMoves;
}
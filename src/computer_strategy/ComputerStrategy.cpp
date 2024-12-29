#include "../../include/computer_strategy/ComputerStrategy.hpp"

#include <chrono>
#include <iostream>

IntPair ComputerStrategy::getMove(const Board& board,
                                  PlayerIDEnum curPlayerId) const {
    auto start = std::chrono::high_resolution_clock::now();

    IntPair move = _calculateMove(board, curPlayerId);

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed =
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Time taken: " << elapsed.count() << " ms\n";
    return move;
}
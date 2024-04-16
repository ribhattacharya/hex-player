#include <iostream>
#include <vector>
#include <random>

#include "../../include/computer_logic/random_move.hpp"
#include "../../include/utility.hpp"

RandomMove::RandomMove() {}

Pair RandomMove::decideNextMove(const Graph &curGraph) const
{
    std::random_device rd;
    std::mt19937 gen(rd());

    // Define the range for the distribution
    std::uniform_int_distribution<> dis(0, curGraph.getSize() - 1);

    // Generate a single random integer
    int row = dis(gen), col = dis(gen);

    return std::make_pair(row, col);
}
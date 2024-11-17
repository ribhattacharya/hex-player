#ifndef COMPUTERSTRATEGY_H
#define COMPUTERSTRATEGY_H

#include "../Types.hpp"
#include "../board/Board.hpp"

class ComputerStrategy {
public:
    virtual ~ComputerStrategy() = default;
    virtual IntPair calculateMove(const Board& board, PlayerIDEnum playerId) = 0;
};

typedef std::unique_ptr<ComputerStrategy> ComputerStrategyPtr;

#endif // COMPUTERSTRATEGY_H
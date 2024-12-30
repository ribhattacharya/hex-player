#ifndef COMPUTERSTRATEGY_H
#define COMPUTERSTRATEGY_H

#include "../Types.hpp"
#include "../board/Board.hpp"

class ComputerStrategy {
public:
    virtual ~ComputerStrategy() = default;
    IntPair getMove(const Board& board, PlayerIDEnum curPlayerId) const;

private:
    virtual IntPair _calculateMove(const Board& board,
                                   PlayerIDEnum curPlayerId) const = 0;
};

typedef std::unique_ptr<ComputerStrategy> ComputerStrategyPtr;

#endif  // COMPUTERSTRATEGY_H
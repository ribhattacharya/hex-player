#ifndef MONTECARLO_H
#define MONTECARLO_H

#include "../Types.hpp"
#include "../board/Board.hpp"
#include "ComputerStrategy.hpp"

class MonteCarlo : public ComputerStrategy{
public:
    IntPair calculateMove(const Board& board, PlayerIDEnum playerId) override;
};

#endif // MONTECARLO_H
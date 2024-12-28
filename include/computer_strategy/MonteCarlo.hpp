#ifndef MONTECARLO_H
#define MONTECARLO_H

#include "../Types.hpp"
#include "../board/Board.hpp"
#include "ComputerStrategy.hpp"

class MonteCarlo : public ComputerStrategy{
public:
    IntPair calculateMove(const Board& board, PlayerIDEnum playerId) override;

private:
    const int _NTRIALS = 1000;
};

#endif // MONTECARLO_H
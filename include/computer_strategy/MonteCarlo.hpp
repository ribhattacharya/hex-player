#ifndef MONTECARLO_H
#define MONTECARLO_H

#include "../Types.hpp"
#include "../board/Board.hpp"
#include "ComputerStrategy.hpp"

class MonteCarlo : public ComputerStrategy {
private:
    const int _NTRIALS = 100;
    PlayerIDEnum _getOtherPlayerID(PlayerIDEnum& playerId) const;
    VectIntPair _getAvailableMoves(const Board& board) const;
    IntPair _calculateMove(const Board& board,
                           PlayerIDEnum curPlayerId) const override;
};

#endif  // MONTECARLO_H
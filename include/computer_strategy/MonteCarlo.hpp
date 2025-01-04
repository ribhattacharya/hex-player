#ifndef MONTECARLO_H
#define MONTECARLO_H


#include "Types.hpp"
#include "board/Board.hpp"
#include "computer_strategy/ComputerStrategy.hpp"

class MonteCarlo : public ComputerStrategy {
private:
    const int _NTRIALS = 1000;
    PlayerIDEnum _getNextPlayerID(PlayerIDEnum& playerId) const;
    VectIntPair _getAvailableMoves(const Board& board) const;
    void _resetMoves(Board& simBoard, VectIntPair& movesToReset) const;
    int _evaluateWinsForMove(const Board& board, const IntPair& testMove,
                             PlayerIDEnum& curPlayerId) const;
    IntPair _calculateMove(const Board& board,
                           PlayerIDEnum curPlayerId) const override;
};

#endif  // MONTECARLO_H
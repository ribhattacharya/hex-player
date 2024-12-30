#ifndef MONTECARLO_H
#define MONTECARLO_H

#include <random>

#include "../Types.hpp"
#include "../board/Board.hpp"
#include "ComputerStrategy.hpp"

class MonteCarlo : public ComputerStrategy {
private:
    const int _NTRIALS = 1000;
    PlayerIDEnum _getNextPlayerID(PlayerIDEnum& playerId) const;
    VectIntPair _getAvailableMoves(const Board& board) const;
    void _resetMoves(Board& simBoard, VectIntPair& availableMoves) const;
    bool _didPlayerWin(Board& simBoard, VectIntPair& simAvailableMoves,
                      PlayerIDEnum& curPlayerId) const;
    int _getWinsFromAllTrials(Board& simBoard, VectIntPair& simAvailableMoves,
                              PlayerIDEnum& curPlayerId,
                              std::mt19937& gen) const;
    IntPair _calculateMove(const Board& board,
                           PlayerIDEnum curPlayerId) const override;
};

#endif  // MONTECARLO_H
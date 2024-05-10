#ifndef MONTE_CARLO_H
#define MONTE_CARLO_H

#include <iostream>

#include "IComputerLogic.hpp"

class MonteCarlo : public IComputerLogic
{
private:
    int _nTrials;
    void _simulateNextMoveFromAvailableMoves(Graph &g, std::vector<Pair> &availableMoves, std::mt19937 &gen, PlayerType playerType) const;
    void _collectAvailableNodes(const Graph &g, std::vector<Pair> &avaiableNodes) const;

public:
    MonteCarlo(int nTrials);
    Pair decideNextMove(const Graph &g, const PlayerType curPlayerType) const override;
};

#endif // MONTE_CARLO_H
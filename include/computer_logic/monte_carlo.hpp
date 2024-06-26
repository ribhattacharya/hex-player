#ifndef MONTE_CARLO_H
#define MONTE_CARLO_H

#include <iostream>

#include "IComputerLogic.hpp"

class MonteCarlo : public IComputerLogic
{
private:
    int _nTrials;

public:
    MonteCarlo(int nTrials);
    Pair decideNextMove(const Graph &g) const override;
};

#endif // MONTE_CARLO_H
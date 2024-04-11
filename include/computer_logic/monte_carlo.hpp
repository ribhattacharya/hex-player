#ifndef MONTE_CARLO
#define MONTE_CARLO

#include <iostream>

#include "IComputerLogic.hpp"

class MonteCarlo : public IComputerLogic
{
private:
    int _nTrials;

public:
    MonteCarlo(int nTrials);
    Pair DecideNextMove(Graph &) const override;
};

#endif // MONTE_CARLO
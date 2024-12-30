#ifndef RANDOM_MOVE_H
#define RANDOM_MOVE_H

#include <iostream>

#include "IComputerLogic.hpp"

class RandomMove : public IComputerLogic
{
public:
    RandomMove();
    Pair decideNextMove(const Graph &g) const override;
};

#endif // RANDOM_MOVE_H
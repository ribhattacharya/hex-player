#ifndef COMPUTER_LOGIC_H
#define COMPUTER_LOGIC_H

#include <iostream>

#include "../graph/graph.hpp"
#include "../custom_types.hpp"

// TODO: Add timer for all computer logic and make NVI pattern
class IComputerLogic
{
public:
    virtual ~IComputerLogic() = default;
    virtual Pair decideNextMove(const Graph &g, const PlayerType curPlayerType) const = 0;
};

#endif // COMPUTER_LOGIC_H
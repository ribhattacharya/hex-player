#ifndef COMPUTER_LOGIC
#define COMPUTER_LOGIC

#include <iostream>

#include "../graph/graph.hpp"
#include "../custom_types.hpp"

class IComputerLogic
{
public:
    virtual ~IComputerLogic() = default;
    virtual Pair DecideNextMove(Graph &) const = 0;
};

#endif // COMPUTER_LOGIC
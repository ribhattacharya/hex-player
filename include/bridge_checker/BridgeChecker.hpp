#ifndef BRIDGECHECKER_H
#define BRIDGECHECKER_H

#include "../graph/Graph.hpp"
#include "../Types.hpp"

class BridgeChecker
{
public:
    virtual ~BridgeChecker() = default;
    virtual bool isBridgeFormed(const Graph &graph, PlayerIDEnum playerId, DirectionEnum direction) = 0;
};

typedef std::unique_ptr<BridgeChecker> BridgeCheckerPtr;

#endif // BRIDGECHECKER_H
#ifndef BRIDGECHECKER_H
#define BRIDGECHECKER_H

#include <memory>
#include "Types.hpp"
#include "graph/Graph.hpp"

class BridgeChecker {
public:
    virtual ~BridgeChecker() = default;
    virtual bool isBridgeFormed(const Graph &graph, PlayerIDEnum playerId,
                                DirectionEnum direction) = 0;
};

typedef std::shared_ptr<BridgeChecker> BridgeCheckerPtr;

#endif  // BRIDGECHECKER_H
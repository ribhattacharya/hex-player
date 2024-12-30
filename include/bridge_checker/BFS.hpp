#ifndef BFS_H
#define BFS_H

#include "bridge_checker/BridgeChecker.hpp"

class BFS : public BridgeChecker
{
public:
    BFS();
    bool isValidNeighbour(const IntPair &nodeID, const int MAX_ROWS, const int MAX_COLS) const;
    bool isBridgeFormed(const Graph &graph, PlayerIDEnum playerId, DirectionEnum direction) override;
};
#endif // BFS_H
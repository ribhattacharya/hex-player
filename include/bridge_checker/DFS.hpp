#ifndef DFS_H
#define DFS_H

#include "BridgeChecker.hpp"
class DFS : public BridgeChecker
{
public:
    DFS();
    bool isValidNeighbour(const IntPair &nodeID, const int MAX_ROWS, const int MAX_COLS) const;
    bool isBridgeFormed(const Graph &graph, PlayerIDEnum playerId, DirectionEnum direction) override;
};

#endif // DFS_H
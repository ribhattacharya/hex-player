#ifndef BFS_H
#define BFS_H

#include "BridgeChecker.hpp"

class BFS : public BridgeChecker
{
public:
    BFS();
    bool isBridgeFormed(const Graph &graph, PlayerIDEnum playerId, DirectionEnum direction) override;
};
#endif // BFS_H
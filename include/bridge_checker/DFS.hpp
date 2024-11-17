#ifndef DFS_H
#define DFS_H

#include "BridgeChecker.hpp"
class DFS : public BridgeChecker
{
public:
    DFS();
    bool isBridgeFormed(const Graph &graph, PlayerIDEnum playerId, DirectionEnum direction) override;
};

#endif // DFS_H
#ifndef BOARD_H
#define BOARD_H

#include "../Types.hpp"
#include "../graph/Graph.hpp"
#include "../bridge_checker/BridgeChecker.hpp"

class Board {
public:
    Board(int size, BridgeCheckerPtr bridgeChecker);
    void placeMove(IntPair move, PlayerIDEnum playerId);  // Places a move
    bool isValidMove(IntPair move) const;
    bool isGameFinishedForPlayer(PlayerIDEnum playerId) const;

private:
    int _size;
    Graph _graph;
    BridgeCheckerPtr _bridgeChecker;
};

#endif  // BOARD_H
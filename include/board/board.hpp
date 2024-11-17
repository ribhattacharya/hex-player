#ifndef BOARD_H
#define BOARD_H

#include "../Types.hpp"
#include "../bridge_checker/BridgeChecker.hpp"
#include "../graph/Graph.hpp"

class Board {
public:
    Board(int size, BridgeCheckerPtr bridgeChecker);
    void placeMove(IntPair move, PlayerIDEnum playerId);
    bool isValidMove(IntPair move) const;
    bool isGameFinishedForPlayer(PlayerIDEnum playerId) const;
    void printBoard() const;
    int getSize() const;

private:
    const int _size;
    Graph _graph;
    BridgeCheckerPtr _bridgeChecker;
};

#endif  // BOARD_H
#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

#include "../player/IPlayer.hpp"
#include "../graph/graph.hpp"
#include "../graph/node.hpp"
#include "../custom_types.hpp"

class Board
{
    int _SIZE;
    Graph _g;
    vspIPlayer _players;
    std::unordered_map<Player, uspNode > _starts;
    std::unordered_map<Player, uspNode > _goals;

    void _saveStartAndGoalNodes(spIPlayer player, std::string orientation);
    bool _checkWinner(spIPlayer player);
    void _makeMove(spIPlayer player);

    // void printGraph() const;
    // void printGraphData() const;

public:
    Board(int size, vspIPlayer players);

    void playGame();
};

#endif // BOARD_H
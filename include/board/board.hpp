#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

#include "../player/Player.hpp"
#include "../graph/graph.hpp"
#include "../graph/node.hpp"
#include "../custom_types.hpp"

class Board
{
    const int _SIZE;
    Graph _g;
    vspPlayer _players;
    std::unordered_map<spPlayer, PlayerGameData> _playersGameData;

    void _initPlayerGameData(spPlayer player, PlayerOrientation orientation);
    bool _checkWinner(spPlayer player);
    void _makeMove(spPlayer player);

public:
    Board(const int size, vspPlayer players);

    void playGame();
};

#endif // BOARD_H
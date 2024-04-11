#ifndef BOARD
#define BOARD

#include <iostream>
#include <vector>
#include <string>

#include "../player/IPlayer.hpp"
#include "../graph/graph.hpp"

class Board
{
    int _SIZE;
    Graph _g;
    std::vector<std::shared_ptr<IPlayer>> _players;

    void _saveStartAndGoalNodes(std::shared_ptr<IPlayer>, std::string);
    bool _checkWinner(std::shared_ptr<IPlayer>) const;
    void _makeMove(std::shared_ptr<IPlayer>);

    // void printGraph() const;
    // void printGraphData() const;

public:
    Board(int, std::vector<std::shared_ptr<IPlayer>>);
    ~Board() {}

    void playGame();
};

#endif // BOARD
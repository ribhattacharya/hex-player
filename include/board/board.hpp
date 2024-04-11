#ifndef BOARD
#define BOARD

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

#include "../player/IPlayer.hpp"
#include "../graph/graph.hpp"

class Board
{
    int _SIZE;
    Graph _g;
    std::vector<std::shared_ptr<IPlayer> > _players;
    std::unordered_map<Player, std::unordered_set<Node *> > _starts;
    std::unordered_map<Player, std::unordered_set<Node *> > _goals;

    void _saveStartAndGoalNodes(std::shared_ptr<IPlayer>, std::string);
    bool _checkWinner(std::shared_ptr<IPlayer>);
    void _makeMove(std::shared_ptr<IPlayer>);

    // void printGraph() const;
    // void printGraphData() const;

public:
    Board(int, std::vector<std::shared_ptr<IPlayer> >);
    ~Board() {}

    void playGame();
};

#endif // BOARD
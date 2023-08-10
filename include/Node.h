#ifndef NODE_H
#define NODE_H

#include <vector>

using std::vector;

enum class Player
{
    HUMAN,
    COMP,
    NONE
};

class Node
{
    /*
    DESC: Create the nodes and helper functions.
    */
    const int ID;
    Player player;
    vector<Node *> neighbours;

public:
    Node(int identifier) : ID(identifier), player(Player::NONE), neighbours() {}

    const int getID() { return ID; }
    const vector<Node *> &getNeighbours() { return neighbours; }
    void setPlayer(Player p) { player = p; }
    const Player getPlayer() { return player; }
    void setNeighbours(vector<Node *> &neighbours) { this->neighbours = neighbours; }
};

#endif // NODE_H
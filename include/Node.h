#ifndef NODE_H
#define NODE_H

#include <vector>

#include "player/enumPlayer.h"

using std::vector;


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

    int GetID() const { return ID; }
    vector<Node *> &GetNeighbours() { return neighbours; }
    void SetNeighbours(vector<Node *> &neighbours) { this->neighbours = neighbours; }
    Player GetPlayer() { return player; }
    void SetPlayer(Player p) { player = p; }
};

#endif // NODE_H
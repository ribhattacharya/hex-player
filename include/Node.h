#ifndef NODE_H
#define NODE_H

#include <vector>

#include "utility.h"
#include "player/enumPlayer.h"

using std::vector;

class Node
{
    /*
    DESC: Create the nodes and helper functions.
    */
    const int ID;
    const Pair idx;
    Player player;
    node_vect neighbours;

public:
    Node(int i, int j, int id) : ID(id), idx(std::make_pair(i, j)), player(Player::NONE), neighbours() {}

    int GetID() const { return ID; }
    Pair GetIdx() const { return idx; }
    node_vect &GetNeighbours() { return neighbours; }
    void SetNeighbours(node_vect &neighbours) { this->neighbours = neighbours; }
    Player GetPlayer() { return player; }
    void SetPlayer(Player p) { player = p; }
};

#endif // NODE_H
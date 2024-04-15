#ifndef NODE_H
#define NODE_H

#include <vector>

#include "../enums.hpp"
#include "../custom_types.hpp"

class Node
{
    const Pair _IDX;
    const int _ID;
    Player _player;
    // TODO: possible optimization here in &_neighbours
    vspNode _neighbours;

public:
    Node(int i, int j, int id);

    Pair GetIDX() const;
    int GetID() const;
    Player GetPlayer();
    void SetPlayer(Player p);
    vspNode GetNeighbours();
    void SetNeighbours(vspNode &neighbours);
};

#endif // NODE_H
#ifndef NODE
#define NODE

#include <vector>

#include "utility.hpp"
#include "player/enum_player.hpp"

class Node
{
    const Pair _IDX;
    const int _ID;
    Player _player;
    node_vect _neighbours;

public:
    Node(int i, int j, int id);

    Pair GetIDX() const;
    int GetID() const;
    Player GetPlayer();
    void SetPlayer(Player p);
    node_vect GetNeighbours() { return _neighbours; }
    void SetNeighbours(node_vect &neighbours) { this->_neighbours = neighbours; }
};

#endif // NODE
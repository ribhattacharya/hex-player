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
    std::vector<std::shared_ptr<Node> > _neighbours;

public:
    Node(int i, int j, int id);

    Pair GetIDX() const;
    int GetID() const;
    Player GetPlayer();
    void SetPlayer(Player p);
    std::vector<std::shared_ptr<Node> > GetNeighbours();
    void SetNeighbours(std::vector<std::shared_ptr<Node> > &neighbours);
};

#endif // NODE_H
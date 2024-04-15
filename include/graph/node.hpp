#ifndef NODE_H
#define NODE_H

#include <vector>
#include <queue>
#include <unordered_set>

#include "../enums.hpp"
#include "../custom_types.hpp"

class Node; // forward declarion so that typedefs can be defined

typedef std::shared_ptr<Node> spNode;
typedef std::vector<spNode> vspNode;
typedef std::vector<vspNode> vvspNode;
typedef std::unordered_set<spNode> uspNode;
typedef std::queue<spNode> qspNode;

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
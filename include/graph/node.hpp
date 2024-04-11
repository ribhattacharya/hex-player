#ifndef NODE
#define NODE

#include <vector>

#include "../player/enum_player.hpp"
#include "../custom_types.hpp"

class Node
{
    const Pair _IDX;
    const int _ID;
    Player _player;
    std::vector<Node *> _neighbours;

public:
    Node(int i, int j, int id);

    Pair GetIDX() const;
    int GetID() const;
    Player GetPlayer();
    void SetPlayer(Player p);
    std::vector<Node *> GetNeighbours();
    void SetNeighbours(std::vector<Node *> &neighbours);
};

#endif // NODE
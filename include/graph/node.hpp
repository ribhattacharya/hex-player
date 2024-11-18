#ifndef NODE_H
#define NODE_H

#include <stack>
#include <unordered_set>

#include "../Types.hpp"

class Node {
public:
    Node(int i, int j);
    Node(const Node &other);
    IntPair getID() const;
    PlayerIDEnum getOccupancy() const;
    void setOccupancy(PlayerIDEnum p);

private:
    const IntPair _nodeID;
    PlayerIDEnum _occupancy;
};

typedef std::vector<Node> Vect1DNode;
typedef std::vector<Vect1DNode> Vect2DNode;
typedef const Node *NodePtr;
typedef std::stack<NodePtr> NodePtrStack;
typedef std::unordered_set<NodePtr> NodePtrSet;

#endif  // NODE_H
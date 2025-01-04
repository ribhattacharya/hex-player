#ifndef NODE_H
#define NODE_H

#include <memory>
#include <queue>
#include <stack>
#include <unordered_set>
#include <unordered_map>

#include "Types.hpp"

class Node {
public:
    Node(int i, int j);
    Node(int i, int j, PlayerIDEnum p);
    Node(const Node &other);
    IntPair getID() const;

private:
    const IntPair _nodeID;
    PlayerIDEnum _occupancy;
    PlayerIDEnum getOccupancy() const;
    void setOccupancy(PlayerIDEnum p);

    friend class Graph;
};

typedef std::vector<Node> Vect1DNode;
typedef std::vector<Vect1DNode> Vect2DNode;
typedef std::shared_ptr<Node> NodePtr;
typedef std::stack<NodePtr> NodePtrStack;
typedef std::queue<NodePtr> NodePtrQueue;
typedef std::unordered_set<NodePtr> NodePtrSet;
typedef std::unordered_map<IntPair, NodePtr> NodePtrMap;

#endif  // NODE_H
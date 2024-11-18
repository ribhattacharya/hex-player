#ifndef GRAPH_H
#define GRAPH_H

#include "../Types.hpp"
#include "Node.hpp"

class Graph {
public:
    Graph(int size);
    Graph(const Graph &other);
    int getSize() const;
    PlayerIDEnum getNodeOccupancy(IntPair pos) const;
    void setNodeOccupancy(IntPair pos, PlayerIDEnum playerId);
    NodePtr getNode(IntPair pos) const;

private:
    const int _size;
    Vect2DNode _nodes;
};

#endif  // GRAPH_H
#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <random>
#include <cstdlib>
#include <iomanip>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <queue>

#include "node.hpp"
#include "../enums.hpp"
#include "../custom_types.hpp"

class Graph
{
    /*
    DESC: Graph class to create and process the graph.
    */
    const int _SIZE;
    vvspNode _nodes;
    void _createEdges();

    template <typename T>
    bool _isInSet(T node, std::unordered_set<T> &set) const;

public:
    Graph(int);
    Graph(const Graph &other);

    int getSize() const;
    spNode getNode(Pair idx) const;
    bool isAvailable(Pair idx) const;
    void setPlayer(Pair idx, PlayerType playertype);
    bool isBridgeFormed(uspNode &STARTS, uspNode &GOALS, PlayerType playertype) const;
};

#endif // GRAPH_H
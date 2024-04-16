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
    // TODO: add __ to all private methods
    int SIZE;
    vvspNode nodes;
    void createEdges();

    template <typename T>
    bool IsInSet(T node, std::unordered_set<T> &set) const;

public:
    Graph(int);
    Graph(const Graph &other);

    int GetSize() const;
    spNode GetNode(Pair idx) const;
    bool IsAvailable(Pair idx) const;
    void SetPlayer(Pair idx, Player playertype);
    bool IsBridgeFormed(uspNode &STARTS, uspNode &GOALS, Player playertype) const;
};

#endif // GRAPH_H
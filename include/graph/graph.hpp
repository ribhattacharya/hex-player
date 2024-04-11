#ifndef GRAPH
#define GRAPH

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
#include "../player/enum_player.hpp"
#include "../custom_types.hpp"

// TODO: Major Refactor Monte Carlo code
// TODO: Add comments
class Graph
{
    /*
    DESC: Graph class to create and process the graph.
    */
    int SIZE;
    std::vector<std::vector<Node *> > nodes;
    void createEdges();

    template <typename T>
    bool IsInSet(T node, std::unordered_set<T> &set) const;

public:
    Graph() {}
    Graph(int);
    Graph(const Graph &other);
    ~Graph();

    int GetSize();
    Node *GetNode(Pair) const;
    bool IsAvailable(Pair idx) const;
    void SetPlayer(Pair, Player);
    bool IsBridgeFormed(std::unordered_set<Node *>, std::unordered_set<Node *>, Player) const;
    void printGraph() const;
};

#endif // GRAPH
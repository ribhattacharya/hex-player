/**
 * @file Graph.h
 * @author Rishabh Bhattacharya (ribhattacharya@ucsd.edu)
 * @brief
 * @version 0.1
 * @date 2023-Aug-10
 *
 * @copyright Copyright (c) 2023
 *
 */
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

#include "node.h"
#include "player/enumPlayer.h"
#include "player/IPlayer.h"
#include "utility.h"

using std::cin;
using std::cout;
using std::endl;
using std::left;
using std::mt19937;
using std::queue;
using std::random_device;
using std::right;
using std::setw;
using std::string;
using std::uniform_int_distribution;
using std::unordered_map;
using std::unordered_set;
using std::vector;

// TODO: Add Monte Carlo code
class Graph
{
    /*
    DESC: Graph class to create and process the graph.
    */
    const int SIZE;
    vector<vector<Node *>> nodes;
    void createEdges();
    template <typename T>
    bool IsInSet(T node, unordered_set<T>& set) const;

public:
    Graph(int);
    ~Graph();

    Node *GetNode(Pair) const;
    bool IsAvailable(Pair idx) const;
    void SetPlayer(Pair, Player);
    bool IsBridgeFormed(IPlayer *) const;
};

Graph::Graph(int s) : SIZE(s), nodes(SIZE, vector<Node *>(SIZE))
{
    cout << "Initialized board with size = " << SIZE << ".\n"
         << endl;

    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            nodes[i][j] = new Node(i * SIZE + j);

    createEdges();
}

/// @brief Graph destructor, deletes all nodes.
Graph::~Graph()
{
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            nodes[i][j] = (delete nodes[i][j], nullptr);
}

/// @brief Create edges between all nodes.
void Graph::createEdges()
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            // 6 directions
            vector<vector<int>> directions{
                {i, j - 1},
                {i - 1, j},
                {i - 1, j + 1},
                {i, j + 1},
                {i + 1, j},
                {i + 1, j - 1}};

            vector<Node *> neighbours;
            for (const auto dir : directions)
            {
                int ii = dir[0], jj = dir[1];
                if (ii >= 0 && ii < SIZE && jj >= 0 && jj < SIZE)
                    neighbours.push_back(nodes[ii][jj]);
            }
            nodes[i][j]->SetNeighbours(neighbours);
        }
    }
}

Node *Graph::GetNode(Pair idx) const
{
    return nodes[idx.first][idx.second];
}

bool Graph::IsAvailable(Pair idx) const
{
    return GetNode(idx)->GetPlayer() == Player::NONE;
}

void Graph::SetPlayer(Pair idx, Player playertype)
{
    GetNode(idx)->SetPlayer(playertype);
}

template <typename T>
bool Graph::IsInSet(T node, unordered_set<T> &set) const
{
    return set.find(node) != set.end();
}

bool Graph::IsBridgeFormed(IPlayer *player) const
{
    unordered_set<Node *> STARTS = player->GetStarts();
    unordered_set<Node *> GOALS = player->GetGoals();
    Player playertype = player->GetPlayerType();

    /*
    If one start node branches into a tree, then it will not lead to a goal iff
    it is a detached tree. In that case, all the nodes will be addeed to CLOSED
    and OPEN will be empty.

    But a case arises if one start node tree contains another start node.
    If the other start node could lead to a target/goal, it would during the same run.
    If not, then going through it again wouldn't help. So we can skip start nodes if they
    are part of CLOSED already.
    */

    queue<Node *> OPEN;
    unordered_set<Node *> CLOSED;

    for (auto start : STARTS)
    {
        if (start->GetPlayer() != playertype || IsInSet(start, CLOSED))
            continue;

        OPEN.push(start);
        while (!OPEN.empty())
        {
            Node *nodeToExpand = OPEN.front();
            OPEN.pop();
            CLOSED.insert(nodeToExpand);

            if (GOALS.find(nodeToExpand) != GOALS.end())
                return true;

            for (auto neighbour : nodeToExpand->GetNeighbours())
            {
                if (neighbour->GetPlayer() != playertype || IsInSet(neighbour, CLOSED))
                    continue;

                OPEN.push(neighbour);
            }
        }
    }

    return false;
}

#endif // GRAPH_H
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <memory>

#include "../../include/graph/graph.hpp"
#include "../../include/graph/node.hpp"

using std::vector;
using std::cout;
using std::string;
using std::unordered_set;

Graph::Graph(int s) : _SIZE(s), _nodes(_SIZE, vspNode(_SIZE))
{
    cout << "Initialized board with size = " << _SIZE << ".\n\n";

    for (int i = 0; i < _SIZE; i++)
        for (int j = 0; j < _SIZE; j++)
            _nodes[i][j] = std::make_shared<Node>(i, j, i * _SIZE + j);

    _createEdges();
}

Graph::Graph(const Graph &other) : _SIZE(other._SIZE)
{
    // Create a new vector of nodes with the same size
    _nodes = vvspNode(_SIZE, vspNode(_SIZE));

    // Copy the content of each node from the other graph
    // Assuming Node has its own copy constructor or clone method
    for (int i = 0; i < _SIZE; i++)
        for (int j = 0; j < _SIZE; j++)
            _nodes[i][j] = std::make_shared<Node>(*other._nodes[i][j]);

    _createEdges();
}

/// @brief Create edges between all nodes.
void Graph::_createEdges()
{
    for (int i = 0; i < _SIZE; i++)
    {
        for (int j = 0; j < _SIZE; j++)
        {
            // 6 directions
            vector<vector<int> > directions{
                {i, j - 1},
                {i - 1, j},
                {i - 1, j + 1},
                {i, j + 1},
                {i + 1, j},
                {i + 1, j - 1}};

            vspNode neighbours;
            for (const auto dir : directions)
            {
                int ii = dir[0], jj = dir[1];
                if (ii >= 0 && ii < _SIZE && jj >= 0 && jj < _SIZE)
                    neighbours.push_back(_nodes[ii][jj]);
            }
            _nodes[i][j]->setNeighbours(neighbours);
        }
    }
}

int Graph::getSize() const { return _SIZE; }

spNode Graph::getNode(Pair idx) const
{
    return _nodes[idx.first][idx.second];
}

bool Graph::isAvailable(Pair idx) const
{
    return getNode(idx)->getPlayer() == PlayerType::NONE;
}

void Graph::setPlayer(Pair idx, PlayerType playertype)
{
    // cout << "setting " << idx << " to be " << playertype << "\n";
    getNode(idx)->setPlayer(playertype);
    // cout << "set " << idx << " to be " << GetNode(idx)->GetPlayer() << "\n";
}

template <typename T>
bool Graph::_isInSet(T node, unordered_set<T> &set) const
{
    return set.find(node) != set.end();
}

// TODO: make this spPlayer based instead of playertype based
bool Graph::isBridgeFormed(uspNode &STARTS, uspNode &GOALS, PlayerType playertype) const
{
    /*
    If one start node branches into a tree, then it will not lead to a goal iff
    it is a detached tree. In that case, all the nodes will be addeed to CLOSED
    and OPEN will be empty.

    But a case arises if one start node tree contains another start node.
    If the other start node could lead to a target/goal, it would during the same run.
    If not, then going through it again wouldn't help. So we can skip start nodes if they
    are part of CLOSED already.
    */
    // cout << "\n\ninside brige function\n\n";
    // for (auto start : STARTS)
    //     cout << start->GetIDX() << " ";
    // cout << '\n';
    // for (auto goal : GOALS)
    //     cout << goal->GetIDX() << " ";
    // cout << '\n';

    // for (auto row : nodes)
    //     for (auto node : row)
    //         cout << node << " " << node->GetIDX() << " has " << node->GetPlayer() << '\n';

    qspNode OPEN;
    uspNode CLOSED;

    for (auto start : STARTS)
    {
        // cout << "\nexpanding node " << start->GetIDX() << " " << start << " of type " << start->GetPlayer() << '\n';
        // for (auto neighbour : start->GetNeighbours())
        //     cout << "node " << start->GetIDX() << " is " << start->GetPlayer()
        //          << " and has neighbour " << neighbour->GetIDX() << " of type " << neighbour->GetPlayer() << '\n';

        if (start->getPlayer() != playertype || _isInSet(start, CLOSED))
            continue;
        // cout << "\nfirst step cleared";
        OPEN.push(start);
        while (!OPEN.empty())
        {
            // cout << "\ninside while loop";
            spNode nodeToExpand = OPEN.front();
            OPEN.pop();
            CLOSED.insert(nodeToExpand);
            // cout << "\nexpanding " << nodeToExpand->GetIDX();

            if (GOALS.find(nodeToExpand) != GOALS.end())
                return true;
            // cout << "\nisnt in GOALS";
            for (auto neighbour : nodeToExpand->getNeighbours())
            {
                // cout << nodeToExpand->GetIDX() << " has neighbour " << neighbour->GetIDX() << '\n';
                // cout << neighbour->GetIDX() << " has " << neighbour->GetPlayer() << '\n';
                if (neighbour->getPlayer() != playertype || _isInSet(neighbour, CLOSED))
                    continue;

                OPEN.push(neighbour);
            }
        }
    }

    return false;
}
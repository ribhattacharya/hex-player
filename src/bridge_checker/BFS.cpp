#include "bridge_checker/BFS.hpp"

#include <iostream>

#include "Utility.hpp"
#include "graph/Node.hpp"

BFS::BFS() {
}

bool BFS::isBridgeFormed(const Graph &graph, PlayerIDEnum playerId,
                         DirectionEnum direction) {
    NodePtrQueue OPEN;
    NodePtrSet GOALS, VISITED;

    // TODO: Refactor according to DFS iomplementstion
    // Add starts and goals
    for (int i = 0; i < graph.getSize(); i++) {
        // Add starts
        IntPair nodeID = (direction == DirectionEnum::HORIZONTAL)
                             ? IntPair({i, 0})
                             : IntPair({0, i});
        NodePtr start = graph.getNode(nodeID);
        // Add start if it is owned by the player
        if (start->getOccupancy() == playerId) {
            OPEN.push(start);
        }

        // Add goals
        nodeID = (direction == DirectionEnum::HORIZONTAL)
                     ? IntPair({i, graph.getSize() - 1})
                     : IntPair({graph.getSize() - 1, 1});
        NodePtr goal = graph.getNode(nodeID);
        // Add goal if it is owned by the player
        if (goal->getOccupancy() == playerId) {
            GOALS.insert(goal);
        }
    }

    // 6 directions
    Vect2DInt delta{{0, -1}, {-1, 0}, {-1, 1}, {0, 1}, {1, 0}, {1, -1}};

    // DFS
    while (!OPEN.empty() && !GOALS.empty()) {
        NodePtr node = OPEN.front();
        OPEN.pop();
        std::cout << "Visiting node " << node->getID() << std::endl;
        // Check if the node is already visited, since a START neighbour can be
        // added to the stack AGAIN during DFS.
        if (VISITED.find(node) != VISITED.end()) {
            continue;
        }
        VISITED.insert(node);

        for (const auto &dir : delta) {
            IntPair neighbourID = {node->getID().first + dir[0],
                                   node->getID().second + dir[1]};
            // Check if the neighbour node exists
            if (neighbourID.first < 0 || neighbourID.first >= graph.getSize() ||
                neighbourID.second < 0 ||
                neighbourID.second >= graph.getSize()) {
                continue;
            }

            NodePtr neighbour = graph.getNode(neighbourID);
            // Check if the neighbour node is owned by the player or if it is
            // already visited
            if (neighbour->getOccupancy() != playerId ||
                VISITED.find(neighbour) != VISITED.end()) {
                continue;
            }

            // Check if the neighbour node is a goal
            if (GOALS.find(neighbour) != GOALS.end()) {
                return true;
            }

            OPEN.push(neighbour);
        }
    }
    return false;
}
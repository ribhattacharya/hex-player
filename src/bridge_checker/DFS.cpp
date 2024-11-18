#include "../../include/bridge_checker/DFS.hpp"
#include <iostream>

#include "../../include/graph/Node.hpp"
#include "../../include/Utility.hpp"

DFS::DFS() {
}

bool DFS::isBridgeFormed(const Graph &graph, PlayerIDEnum playerId,
                         DirectionEnum direction) {
    NodePtrStack OPEN;
    NodePtrSet GOALS, VISITED;

    // Get all starts for the given direction
    if (direction == DirectionEnum::HORICONTAL) {
        for (int i = 0; i < graph.getSize(); i++) {
            NodePtr start = graph.getNode({i, 0});
            // Add start if it is owned by the player
            if (start->getOccupancy() == playerId) {
                OPEN.push(start);
            }

            NodePtr goal = graph.getNode({i, graph.getSize() - 1});
            // Add goal if it is owned by the player
            if (goal->getOccupancy() == playerId) {
                GOALS.insert(goal);
            }
        }
    }

    // Get all starts for the given direction
    if (direction == DirectionEnum::VERTICAL) {
        for (int i = 0; i < graph.getSize(); i++) {
            // Add start if it is owned by the player
            NodePtr start = graph.getNode({0, i});
            if (start->getOccupancy() == playerId) {
                OPEN.push(start);
            }

            NodePtr goal = graph.getNode({graph.getSize() - 1, 1});
            // Add goal if it is owned by the player
            if (goal->getOccupancy() == playerId) {
                GOALS.insert(goal);
            }
        }
    }

    // 6 directions
    Vect2DInt delta{{0, -1}, {-1, 0}, {-1, 1}, {0, 1}, {1, 0}, {1, -1}};

    while (!OPEN.empty() && !GOALS.empty()) {
        NodePtr node = OPEN.top();
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
            // Check if the neighbour is out of bounds
            if (neighbourID.first < 0 || neighbourID.first >= graph.getSize() ||
                neighbourID.second < 0 ||
                neighbourID.second >= graph.getSize()) {
                continue;
            }

            NodePtr neighbour = graph.getNode(neighbourID);

            if (GOALS.find(neighbour) != GOALS.end()) {
                return true;
            }
            if (neighbour->getOccupancy() != playerId ||
                VISITED.find(neighbour) != VISITED.end()) {
                continue;
            }
            OPEN.push(neighbour);
        }
    }
    return false;
}
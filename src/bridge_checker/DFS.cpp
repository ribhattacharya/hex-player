#include "bridge_checker/DFS.hpp"

#include "Types.hpp"
#include "graph/Node.hpp"

DFS::DFS() {
}

bool DFS::isValidNeighbour(const IntPair& nodeID, const int MAX_ROWS,
                           const int MAX_COLS) const {
    return nodeID.first >= 0 && nodeID.first < MAX_ROWS && nodeID.second >= 0 &&
           nodeID.second < MAX_COLS;
}

bool DFS::isBridgeFormed(const Graph& graph, PlayerIDEnum playerId,
                         DirectionEnum direction) {
    NodePtrStack OPEN;
    NodePtrSet GOALS, VISITED;

    // Add starts and goals
    for (int i = 0; i < graph.getSize(); i++) {
        IntPair start_pos, goal_pos;

        if (direction == DirectionEnum::HORIZONTAL) {
            start_pos = {i, 0};
            goal_pos = {i, graph.getSize() - 1};
        } else {
            start_pos = {0, i};
            goal_pos = {graph.getSize() - 1, i};
        }

        // Add start if it is owned by the player
        if (graph.getNodeOccupancy(start_pos) == playerId) {
            NodePtr startNode = graph.getNode(start_pos);
            OPEN.push(startNode);
            VISITED.insert(startNode);
        }

        // Add goal if it is owned by the player
        if (graph.getNodeOccupancy(goal_pos) == playerId) {
            GOALS.insert(graph.getNode(goal_pos));
        }
    }

    // Early exit if no goals found
    if (GOALS.empty()) {
        return false;
    }

    // 6 directions for hexagonal grid
    Vect2DInt delta{{0, -1}, {-1, 0}, {-1, 1}, {0, 1}, {1, 0}, {1, -1}};

    // DFS
    while (!OPEN.empty()) {
        NodePtr node = OPEN.top();
        OPEN.pop();

        // Check if the current node is a goal
        if (GOALS.find(node) != GOALS.end()) {
            return true;
        }

        for (const auto& dir : delta) {
            IntPair neighbourID = {node->getID().first + dir[0],
                                   node->getID().second + dir[1]};

            // Skip if node doesn't exist or not owned by player
            if (!graph.nodeExists(neighbourID) ||
                graph.getNodeOccupancy(neighbourID) != playerId) {
                continue;
            }

            NodePtr neighbour = graph.getNode(neighbourID);

            // Skip if already visited
            if (VISITED.find(neighbour) != VISITED.end()) {
                continue;
            }

            VISITED.insert(neighbour);
            OPEN.push(neighbour);
        }
    }
    return false;
}
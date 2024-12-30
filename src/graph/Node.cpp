#include "graph/Node.hpp"

Node::Node(int i, int j)
    : _nodeID(std::make_pair(i, j)), _occupancy(PlayerIDEnum::NONE) {
}
Node::Node(const Node &other)
    : _nodeID(other._nodeID), _occupancy(other._occupancy) {
}

IntPair Node::getID() const {
    return _nodeID;
}

PlayerIDEnum Node::getOccupancy() const {
    return _occupancy;
}

void Node::setOccupancy(PlayerIDEnum p) {
    _occupancy = p;
}
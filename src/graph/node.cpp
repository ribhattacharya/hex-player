#include "../../include/graph/node.hpp"

Node::Node(int i, int j, int id) : _IDX(std::make_pair(i, j)), _ID(id), _player(Player::NONE) {}

Pair Node::GetIDX() const { return _IDX; }

int Node::GetID() const { return _ID; }

Player Node::GetPlayer() { return _player; }

void Node::SetPlayer(Player p) { _player = p; }

vspNode Node::GetNeighbours() { return _neighbours; }

void Node::SetNeighbours(vspNode &neighbours) { this->_neighbours = neighbours; }
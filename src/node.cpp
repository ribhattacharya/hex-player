#include "include/node.hpp"

Node::Node(int i, int j, int id) : _IDX(std::make_pair(i, j)), _ID(id), _player(Player::NONE), _neighbours() {}

Pair Node::GetIDX() const { return _IDX; }

int Node::GetID() const { return _ID; }

Player Node::GetPlayer() { return _player; }

void Node::SetPlayer(Player p) { _player = p; }

node_vect Node::GetNeighbours() { return _neighbours; }

void Node::SetNeighbours(node_vect &neighbours) { this->_neighbours = neighbours; }
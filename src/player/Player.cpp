#include "../../include/player/Player.hpp"

Player::Player(std::string name, PlayerType type) : _playerName(name), _playerType(type) {}

std::string Player::getName() const { return _playerName; }

PlayerType Player::getType() const { return _playerType; }
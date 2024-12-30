#include "player/Player.hpp"

Player::Player(std::string name, PlayerIDEnum playerID)
    : _playerName(name), _playerID(playerID) {
}

PlayerIDEnum Player::getPlayerID() const {
    return _playerID;
}

std::string Player::getName() const {
    return _playerName;
}
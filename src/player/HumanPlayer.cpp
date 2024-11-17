#include "../../include/player/HumanPlayer.hpp"

HumanPlayer::HumanPlayer(std::string name, PlayerIDEnum playerID)
    : Player(name, playerID) {}

IntPair HumanPlayer::makeMove() { return IntPair(0, 0); }
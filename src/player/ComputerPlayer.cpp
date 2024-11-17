#include "../../include/player/ComputerPlayer.hpp"

ComputerPlayer::ComputerPlayer(std::string name, PlayerIDEnum playerID,
                               ComputerStrategyPtr computerStrategy)
    : Player(name, playerID), _computerStrategy(std::move(computerStrategy)) {
}

IntPair ComputerPlayer::makeMove() {
    return IntPair(0, 0);
}
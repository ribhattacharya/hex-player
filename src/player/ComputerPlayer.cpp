#include "../../include/player/ComputerPlayer.hpp"

ComputerPlayer::ComputerPlayer(std::string name, PlayerIDEnum playerID,
                               ComputerStrategyPtr computerStrategy)
    : Player(name, playerID), _computerStrategy(std::move(computerStrategy)) {
}

IntPair ComputerPlayer::makeMove(const Board& board) {
    return _computerStrategy->calculateMove(board, getPlayerID());
}
#ifndef COMPUTERPLAYER_H
#define COMPUTERPLAYER_H

#include "../Types.hpp"
#include "../computer_strategy/ComputerStrategy.hpp"
#include "Player.hpp"

class ComputerPlayer : public Player {
public:
  ComputerPlayer(std::string name, PlayerIDEnum playerID,
                 ComputerStrategyPtr computerStrategy);
  IntPair makeMove(const Board& board) override;

private:
  const ComputerStrategyPtr _computerStrategy;
};

#endif // COMPUTERPLAYER_H
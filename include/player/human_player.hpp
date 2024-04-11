#ifndef HUMAN_PLAYER_H
#define HUMAN_PLAYER_H

#include <string>

#include "IPlayer.hpp"
#include "../enums.hpp"
#include "../graph/graph.hpp"
#include "../custom_types.hpp"

class HumanPlayer : public IPlayer
{
private:
    std::string _playerName;
    Player _playerType = Player::HUMAN;

public:
    HumanPlayer(std::string name); 
    std::string GetPlayerName() const override;
    Player GetPlayerType() const override;
    Pair DecideNextMove(Graph &) const override;
};

#endif // HUMAN_PLAYER_H
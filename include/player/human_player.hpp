#ifndef HUMAN_PLAYER
#define HUMAN_PLAYER

#include <string>

#include "IPlayer.hpp"
#include "enum_player.hpp"
#include "../graph/graph.hpp"

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

#endif // HUMAN_PLAYER
#ifndef COMP_PLAYER_H
#define COMP_PLAYER_H

#include <string>

#include "../computer_logic/IComputerLogic.hpp"
#include "IPlayer.hpp"
#include "../enums.hpp"
#include "../custom_types.hpp"

class CompPlayer : public IPlayer
{
private:
    std::string _playerName;
    Player _playerType = Player::COMP;
    std::shared_ptr<IComputerLogic> _computerLogic;

public:
    CompPlayer(std::string name, std::shared_ptr<IComputerLogic> computerLogic);
    ~CompPlayer() {}

    std::string GetPlayerName() const override;
    Player GetPlayerType() const override;
    Pair DecideNextMove(Graph &) const override;
};

#endif // COMP_PLAYER_H
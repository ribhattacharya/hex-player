#ifndef COMP_PLAYER
#define COMP_PLAYER

#include <string>

#include "../computer_logic/IComputerLogic.hpp"
#include "IPlayer.hpp"
#include "enum_player.hpp"
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

#endif // COMP_PLAYER
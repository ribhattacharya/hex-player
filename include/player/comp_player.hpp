#ifndef COMP_PLAYER_H
#define COMP_PLAYER_H

#include <string>

#include "../computer_logic/IComputerLogic.hpp"
#include "Player.hpp"
#include "../enums.hpp"
#include "../custom_types.hpp"

class CompPlayer : public Player
{
private:
    std::shared_ptr<IComputerLogic> _computerLogic;

public:
    CompPlayer(std::string name, std::shared_ptr<IComputerLogic> computerLogic);

    Pair decideNextMove(const Graph &g) const override;
};

#endif // COMP_PLAYER_H
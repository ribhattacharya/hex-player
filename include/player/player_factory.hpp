#ifndef PLAYER_FACTORY_H
#define PLAYER_FACTORY_H

#include <memory>
#include <string>

#include "IPlayer.hpp"
#include "../enums.hpp"
class PlayerFactory
{
public:
    static spIPlayer createHumanPlayer(std::string name);
    static spIPlayer createCompPlayer(ComputerLogic computerLogic);
};

#endif // PLAYER_FACTORY_H
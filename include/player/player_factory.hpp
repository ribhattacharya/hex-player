#ifndef PLAYER_FACTORY_H
#define PLAYER_FACTORY_H

#include <memory>
#include <string>

#include "IPlayer.hpp"
#include "../enums.hpp"
class PlayerFactory
{
public:
    static spIPlayer CreateHumanPlayer(std::string name);
    static spIPlayer CreateCompPlayer(ComputerLogic computerLogic);
};

#endif // PLAYER_FACTORY_H
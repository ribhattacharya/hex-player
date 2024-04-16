#ifndef PLAYER_FACTORY_H
#define PLAYER_FACTORY_H

#include <memory>
#include <string>

#include "Player.hpp"
#include "../enums.hpp"
class PlayerFactory
{
public:
    static spPlayer createHumanPlayer(std::string name);
    static spPlayer createCompPlayer(ComputerLogic computerLogic);
};

#endif // PLAYER_FACTORY_H
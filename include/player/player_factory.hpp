#ifndef PLAYER_FACTORY_H
#define PLAYER_FACTORY_H

#include <memory>
#include <string>

#include "IPlayer.hpp"
#include "../enums.hpp"
class PlayerFactory
{
public:
    static std::shared_ptr<IPlayer> CreateHumanPlayer(std::string name);
    static std::shared_ptr<IPlayer> CreateCompPlayer(ComputerLogic computerLogic);
};

#endif // PLAYER_FACTORY_H
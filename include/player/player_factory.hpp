#ifndef PLAYER_FACTORY_H
#define PLAYER_FACTORY_H

#include <memory>
#include <string>

#include "Player.hpp"
#include "../enums.hpp"
class PlayerFactory
{
private:
    static int _playersCount;
    static PlayerType _getNextPlayerType();

public:
    static spPlayer createPlayer(std::string humanPlayerName);
    static spPlayer createPlayer(ComputerLogic computerLogic);
};

#endif // PLAYER_FACTORY_H
#ifndef PLAYERFACTORY_H
#define PLAYERFACTORY_H

#include "Types.hpp"
#include "player/Player.hpp"

class PlayerFactory {
public:
    // Get the singleton instance
    static PlayerFactory &getInstance() {
        // Static else instance will be destroyed
        static PlayerFactory playerFactory;
        return playerFactory;
    }

    // Delete copy constructor and assignment operator
    PlayerFactory(const PlayerFactory &) = delete;
    PlayerFactory &operator=(const PlayerFactory &) = delete;

    PlayerPtr createPlayer(const std::string &humanPlayerName);
    PlayerPtr createPlayer(ComputerStrategyEnum computerStrategyEnum);

private:
    PlayerFactory();
    PlayerIDEnum _getPlayerID();
    int _numPlayers;
};

#endif  // PLAYERFACTORY_H
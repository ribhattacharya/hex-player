#include "player/PlayerFactory.hpp"

#include <stdexcept>
#include <utility>

#include "computer_strategy/MonteCarlo.hpp"
#include "computer_strategy/RandomMove.hpp"
#include "player/ComputerPlayer.hpp"
#include "player/HumanPlayer.hpp"

PlayerFactory::PlayerFactory() : _numPlayers(0) {
}

PlayerIDEnum PlayerFactory::_getPlayerID() {
    if (_numPlayers >= 2) {
        throw std::runtime_error("Number of players cannot exceed 2!");
    }
    _numPlayers++;
    return _numPlayers == 1 ? PlayerIDEnum::PLAYER_1 : PlayerIDEnum::PLAYER_2;
}

PlayerPtr PlayerFactory::createPlayer(const std::string &humanPlayerName) {
    PlayerIDEnum playerID = _getPlayerID();
    return std::make_unique<HumanPlayer>(humanPlayerName, playerID);
}

PlayerPtr PlayerFactory::createPlayer(
    ComputerStrategyEnum computerStrategyEnum) {
    PlayerIDEnum playerID = _getPlayerID();
    std::string name = "Computer Player " + std::to_string(_numPlayers);

    ComputerStrategyPtr computerStrategy = nullptr;
    switch (computerStrategyEnum) {
        case ComputerStrategyEnum::MONTE_CARLO:
            computerStrategy = std::make_unique<MonteCarlo>();
            break;
        case ComputerStrategyEnum::RANDOM_MOVE:
            computerStrategy = std::make_unique<RandomMove>();
            break;
        default:
            throw std::invalid_argument("Invalid computer strategy.");
    }

    return std::make_unique<ComputerPlayer>(name, playerID,
                                            std::move(computerStrategy));
}
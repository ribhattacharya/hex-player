#include <iostream>
#include <memory>
#include <string>
#include <cassert>

#include "../../include/player/player_factory.hpp"
#include "../../include/player/human_player.hpp"
#include "../../include/player/comp_player.hpp"
#include "../../include/computer_logic/monte_carlo.hpp"
#include "../../include/computer_logic/random_move.hpp"
#include "../../include/enums.hpp"

int PlayerFactory::_playersCount = 0;

PlayerType PlayerFactory::_getNextPlayerType()
{
    if (_playersCount >= 2)
        throw std::invalid_argument("Maximum number of players reached.");
    
    return static_cast<PlayerType>(_playersCount++);
}

std::shared_ptr<Player> PlayerFactory::createPlayer(std::string humanPlayerName)
{
    PlayerType _playerType = _getNextPlayerType();

    if (humanPlayerName == "")
    {
        std::cout << "Enter name of human player: ";
        std::string name;
        std::cin >> name;
    }
    
    return std::make_shared<HumanPlayer>(humanPlayerName, _playerType);
}

std::shared_ptr<Player> PlayerFactory::createPlayer(ComputerLogic computerLogic)
{
    PlayerType _playerType = _getNextPlayerType();
    int _playerNum = static_cast<int>(_playerType) + 1;

    std::string _name;
    switch (computerLogic)
    {
        case ComputerLogic::MONTE_CARLO:
            _name = "Computer " + std::to_string(_playerNum) + " (Monte Carlo)";
            return std::make_shared<CompPlayer>(_name, 
                                                std::make_shared<MonteCarlo>(100), 
                                                _playerType);
        
        case ComputerLogic::RANDOM_MOVE:
            _name = "Computer " + std::to_string(_playerNum) + " (Random Move)";
            return std::make_shared<CompPlayer>(_name, 
                                                std::make_shared<RandomMove>(), 
                                                _playerType);
        
        default:
            throw std::invalid_argument("Invalid computer logic passed as argument.");
    }
}

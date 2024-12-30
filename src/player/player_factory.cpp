#include <iostream>
#include <memory>
#include <string>

#include "../../include/player/player_factory.hpp"
#include "../../include/player/human_player.hpp"
#include "../../include/player/comp_player.hpp"
#include "../../include/computer_logic/monte_carlo.hpp"
#include "../../include/computer_logic/random_move.hpp"
#include "../../include/enums.hpp"

std::shared_ptr<IPlayer> PlayerFactory::createHumanPlayer(std::string name)
{
    if (name == "")
    {
        std::cout << "Enter name of human player: ";
        std::string name;
        std::cin >> name;
    }

    return std::make_shared<HumanPlayer>(name);
}

std::shared_ptr<IPlayer> PlayerFactory::createCompPlayer(ComputerLogic computerLogic)
{
    switch (computerLogic)
    {
        case ComputerLogic::MONTE_CARLO:
            return std::make_shared<CompPlayer>("Computer Monte Carlo", std::make_shared<MonteCarlo>(100));
        case ComputerLogic::RANDOM_MOVE:
            return std::make_shared<CompPlayer>("Computer Random Move", std::make_shared<RandomMove>());
        default:
            throw std::invalid_argument("Invalid computer logic passed as argument.");
    }
}

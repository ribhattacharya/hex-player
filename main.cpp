#include <iostream>
#include <string>
#include <utility>

#include "Types.hpp"
#include "game/Game.hpp"
#include "player/Player.hpp"
#include "player/PlayerFactory.hpp"

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <board_size>" << std::endl;
        return 1;
    }

    int boardSize = std::stoi(argv[1]);

    PlayerPtr player2 = PlayerFactory::getInstance().createPlayer("Tony Stark");
    PlayerPtr player1 = PlayerFactory::getInstance().createPlayer(ComputerStrategyEnum::MONTE_CARLO);
    
    Game game(boardSize, std::move(player1), std::move(player2));
    game.play();

    return 0;
}
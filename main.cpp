#include <string>
#include <utility>

#include "Types.hpp"
#include "game/Game.hpp"
#include "player/PlayerFactory.hpp"

int main(int argc, char **argv) {
    int boardSize = std::stoi(argv[1]);

    // TODO: Player order selection and print direction
    PlayerPtr player1 = PlayerFactory::getInstance().createPlayer(
        ComputerStrategyEnum::MONTE_CARLO);
    PlayerPtr player2 = PlayerFactory::getInstance().createPlayer("Tony Stark");

    Game game(boardSize, std::move(player1), std::move(player2));
    game.play();

    return 0;
}
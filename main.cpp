#include <utility>

#include "include/Types.hpp"
#include "include/game/Game.hpp"
#include "include/player/PlayerFactory.hpp"

int main(int argc, char **argv) {
    int boardSize = 5;

    PlayerPtr player1 =
        std::move(PlayerFactory::getInstance().createPlayer("Tony Stark"));
    PlayerPtr player2 = std::move(PlayerFactory::getInstance().createPlayer(
        ComputerStrategyEnum::RANDOM_MOVE));

    Game game(boardSize, std::move(player1), std::move(player2));
    game.play();

    return 0;
}
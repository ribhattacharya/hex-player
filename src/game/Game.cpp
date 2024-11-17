#include "../../include/game/Game.hpp"

#include <iostream>

#include "../../include/Types.hpp"
#include "../../include/bridge_checker/BFS.hpp"
#include "../../include/bridge_checker/DFS.hpp"
#include "../../include/player/Player.hpp"

Game::Game(int boardSize, PlayerPtr player1, PlayerPtr player2)
    : board(boardSize, std::make_unique<DFS>()) {
    players.push_back(std::move(player1));
    players.push_back(std::move(player2));
}

bool Game::isGameFinishedForPlayer(PlayerIDEnum playerId) const {
    return false;
}

int Game::play() {
    while (true) {
        for (auto &player : players) {
            std::cout << "Player " << player->getName() << "'s turn"
                      << std::endl;
            IntPair move = player->makeMove();
            while (!board.isValidMove(move)) {
                std::cout << "Invalid move" << std::endl;
                move = player->makeMove();
            }
            board.placeMove(move, player->getPlayerID());

            if (board.isGameFinishedForPlayer(player->getPlayerID())) {
                std::cout << "Player " << player->getName() << " wins!"
                          << std::endl;
                return 0;
            }
        }
    }

    return 1;
}
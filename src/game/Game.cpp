#include "../../include/game/Game.hpp"

#include <iostream>

#include "../../include/Types.hpp"
#include "../../include/Utility.hpp"
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
            board.printBoard();

            std::cout << "Player " << player->getName() << "'s turn"
                      << std::endl;
            // Get Player move until it is valid
            while (true) {
                IntPair move = player->makeMove(board);
                if (board.isValidMove(move)) {
                    std::cout << "Player " << player->getName()
                              << " makes move " << move << std::endl;
                    board.placeMove(move, player->getPlayerID());
                    break;
                }
            }

            // Check if game is finished
            if (board.isGameFinishedForPlayer(player->getPlayerID())) {
                board.printBoard();
                std::cout << "Player " << player->getName() << " wins!"
                          << std::endl;
                return 0;  // Should always terminate here
            }
        }
    }

    return 1;  // Should never get here
}
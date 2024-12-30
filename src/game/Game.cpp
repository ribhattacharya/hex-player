#include "game/Game.hpp"

#include <iostream>
#include <memory>

#include "Types.hpp"
#include "Utility.hpp"
// #include "bridge_checker/BFS.hpp"
#include "bridge_checker/DFS.hpp"
#include "player/Player.hpp"

using std::cout;
using std::endl;

Game::Game(int boardSize, PlayerPtr player1, PlayerPtr player2)
    : board(boardSize, std::make_shared<DFS>()) {
    players.emplace_back(std::move(player1));
    players.emplace_back(std::move(player2));
}

bool Game::_isGameFinishedForPlayer(PlayerIDEnum playerId) const {
    return board.isGameFinishedForPlayer(playerId);
}

void Game::_makeMove(PlayerPtr &player) {
    bool isValidMove = false;
    while (!isValidMove) {
        IntPair move = player->getMove(board);
        isValidMove = board.isValidMove(move);
        if (!isValidMove) {
            cout << "Invalid move by player " << player->getName() << ". Retry."
                 << endl;
            continue;
        }

        cout << "Player " << player->getName() << " makes move " << move
             << endl;
        board.placeMove(move, player->getPlayerID());
    }
}
void Game::play() {
    bool isGameFinished = false;
    while (!isGameFinished) {
        for (auto &player : players) {
            // cout << "\033[2J\033[1;1H";  // Clear screen
            board.printBoard();

            cout << "Player " << player->getName() << "'s turn" << endl;
            _makeMove(player);

            isGameFinished = _isGameFinishedForPlayer(player->getPlayerID());
            if (!isGameFinished) {
                continue;
            } else {
                // cout << "\033[2J\033[1;1H";  // Clear screen
                board.printBoard();
                cout << "Player " << player->getName() << " wins!" << endl;
                break;
            }
        }
    }
}
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

void Game::_makeMove(PlayerPtr& player) {
    bool isValidMove = false;
    while (!isValidMove) {
        IntPair move = player->getMove(board);
        isValidMove = board.isValidMove(move);
        if (!isValidMove) {
            cout << RED << "❌ Invalid move by player " << player->getName()
                 << ". Please try again." << RESET << endl;
            continue;
        }

        cout << GREEN << "✓ " << BOLD << player->getName() << RESET << GREEN
             << " makes move " << CYAN << move << RESET << endl;
        board.placeMove(move, player->getPlayerID());
    }
}
void Game::play() {
    cout << BOLD << CYAN << "\n🎮 Welcome to Hex Game!" << RESET << endl;
    cout << DIM << "Players: " << players[0]->getName() << " (X) vs "
         << players[1]->getName() << " (O)" << RESET << endl;
    cout << string(50, '=') << endl;

    bool isGameFinished = false;
    int turnCount = 0;

    while (!isGameFinished) {
        for (auto& player : players) {
            turnCount++;
            cout << "\n"
                 << BOLD << YELLOW << "🔄 Turn " << turnCount << RESET << endl;
            cout << BOLD << MAGENTA << "🎯 " << player->getName() << "'s turn"
                 << RESET << endl;

            // cout << "\033[2J\033[1;1H";  // Clear screen
            board.printBoard();

            _makeMove(player);

            isGameFinished = _isGameFinishedForPlayer(player->getPlayerID());
            if (isGameFinished) {
                cout << "\n" << string(50, '=') << endl;
                // cout << "\033[2J\033[1;1H";  // Clear screen
                board.printBoard();

                cout << BLINKING_GREEN_HIGHLIGHT << BOLD << "🏆 GAME OVER! "
                     << player->getName() << " WINS! 🏆" << RESET << endl;
                cout << DIM << "Total turns played: " << turnCount << RESET
                     << endl;
                break;
            }
        }
    }
}
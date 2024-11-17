#ifndef GAME_H
#define GAME_H

#include "../player/Player.hpp"
#include "../board/Board.hpp"

class Game {
public:
    Game(int boardSize, PlayerPtr player1, PlayerPtr player2);  // Constructor
    bool isGameFinishedForPlayer(PlayerIDEnum playerId) const;
    int play();  // Starts the game loop
private:
    Board board;  // Game board
    PlayerList players;
};

#endif  // GAME_H
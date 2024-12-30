#ifndef GAME_H
#define GAME_H

#include "player/Player.hpp"
#include "board/Board.hpp"

class Game {
public:
    Game(int boardSize, PlayerPtr player1, PlayerPtr player2);  // Constructor
    void play();

private:
    Board board;
    PlayerList players;
    bool _isGameFinishedForPlayer(PlayerIDEnum playerId) const;
    void _makeMove(PlayerPtr &player);
};

#endif  // GAME_H
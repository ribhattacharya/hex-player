#include <iostream>
#include <string>

#include "../include/player/human_player.hpp"

// using std::cin;
// using std::cout;
// using std::string;

HumanPlayer::HumanPlayer(std::string name) : _playerName(name) {}

std::string HumanPlayer::GetPlayerName() const override { return _playerName; }

Player HumanPlayer::GetPlayerType() const override { return _playerType; }

Pair HumanPlayer::DecideNextMove(Graph &g) const override
{
    char row = 'a', col = 'a';
    std::cout << "Enter row: ";
    std::cin >> row;
    std::cout << "Enter column: ";
    std::cin >> col;

    int i = row - 'a', j = col - 'a';

    // Convert 1-indexed rows and columns into 0-indexed
    return std::make_pair(i, j);
}
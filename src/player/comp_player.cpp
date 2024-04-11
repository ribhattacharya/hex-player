#include <iostream>
#include <string>
#include <memory>

#include "include/player/comp_player.hpp"
#include "include/computer_logic/IComputerLogic.hpp"

using std::cin;
using std::cout;
using std::string;

CompPlayer::CompPlayer(std::string name, std::shared_ptr<IComputerLogic> computerLogic) : _playerName(name), _computerLogic(computerLogic) {}

string CompPlayer::GetPlayerName() const override { return _playerName; }

Player CompPlayer::GetPlayerType() const override { return _playerType; }

Pair CompPlayer::DecideNextMove(Graph &g) const override { return _computerLogic->DecideMove(g); }

// Pair CompPlayer::RandomMove(int SIZE)
// {
//     std::random_device rd;
//     std::mt19937 gen(rd());

//     // Define the range for the distribution
//     std::uniform_int_distribution<> dis(0, SIZE - 1);

//     // Generate a single random integer
//     int row = dis(gen), col = dis(gen);

//     return std::make_pair(row, col);
// }

// void CompPlayer::PassGraph(Graph &g)
// {
//     cout << "Argyument after passing address: " << &g << '\n';
//     curGraph = &g;
//     cout << "curGraph graph address: " << curGraph << '\n';
//     std::cout << "Copied graph size : " << curGraph.GetSize() << "\n\n";
// }
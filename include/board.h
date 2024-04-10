#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
#include <string>

#include "node.h"
#include "graph.h"
#include "player/IPlayer.h"
#include "player/enumPlayer.h"
#include "player/humanPlayer.h"
#include "player/compPlayer.h"
#include "utility.h"

using std::cout;
using std::string;
using std::vector;

class Board
{
    int SIZE;
    Graph g;
    vector<IPlayer *> players;

    void SaveStartAndGoalNodes(IPlayer *, string);

    bool checkWinner(IPlayer *) const;
    void MakeMove(IPlayer *);

    // void printGraph() const;
    void printGraphData() const;

public:
    Board(int, vector<IPlayer *>);
    ~Board() {}

    void playGame();
};

Board::Board(int s, vector<IPlayer *> players) : SIZE(s), g(s)
{
    cout << "Main graph address: " << &g << '\n';
    this->players = players;

    // assert(this->players.size() == 2);

    SaveStartAndGoalNodes(players[1], "vertical");
    SaveStartAndGoalNodes(players[0], "horizontal");

    // for (auto player : players)
    // {
    //     if (player->GetPlayerType() == Player::COMP)
    //     {
    //         Graph gCopy(g);
    //         cout << "Argyument before passing address: " << &gCopy << '\n';
    //         player->PassGraph(gCopy);
    //     }
    // }

    g.printGraph();
}

void Board::SaveStartAndGoalNodes(IPlayer *player, string orientation)
{
    vector<Node *> starts(SIZE), goals(SIZE);

    for (int k = 0; k < SIZE; k++)
    {
        Pair startIdx, goalIdx;

        if (orientation == "vertical")
        {
            startIdx = std::make_pair(0, k);
            goalIdx = std::make_pair(SIZE - 1, k);
        }
        else if (orientation == "horizontal")
        {
            startIdx = std::make_pair(k, 0);
            goalIdx = std::make_pair(k, SIZE - 1);
        }

        starts[k] = g.GetNode(startIdx);
        goals[k] = g.GetNode(goalIdx);
    }

    player->SetStarts(starts);
    player->SetGoals(goals);
}

void Board::playGame()
{
    // By nature of game, it cannot end in draw, so it will terminate.
    while (true)
    {   int instance = 0;
        for (auto player : players)
        {   
            MakeMove(player);
            // cout << "make move" << ++instance << "\n";
            // Graph gCopy(g);
            // cout << "Argument before passing address: " << &gCopy << '\n';
            // players[1]->PassGraph(gCopy);

            if (checkWinner(player))
            {
                cout << '\n' << player->GetPlayerName() << " wins!\n";
                return;
            }
        }
    }

    cout << "\nGame ends in a draw! There's something WRONG!" << endl;
    return;
}

bool Board::checkWinner(IPlayer *player) const
{
    node_set STARTS = player->GetStarts();
    node_set GOALS = player->GetGoals();
    Player playerType = player->GetPlayerType();

    return g.IsBridgeFormed(STARTS, GOALS, playerType);
}

void Board::MakeMove(IPlayer *player)
{
    Graph gCopy(g);
    Pair idx = player->GetMove(gCopy);

    while (!g.IsAvailable(idx))
    {
        cout << idx << "Node not available, try again!\n";
        idx = player->GetMove(gCopy);
    }
    

    Player playertype = player->GetPlayerType();
    g.SetPlayer(idx, playertype);

    std::cout << "\x1B[2J\x1B[H"; // Clear screen
    g.printGraph();
}

// TODO: Make printing symbols instance based rather than enum based
// void Board::printGraph() const
// {

//     unordered_map<Player, char> symbols = {
//         {Player::HUMAN, 'X'},
//         {Player::COMP, 'O'},
//         {Player::NONE, '.'}};

//     cout << string(3, ' ');
//     for (int col = static_cast<int>('a'), j = 0; j < SIZE; j++, col++)
//     {
//         cout << '|' << static_cast<char>(col) << '|';
//         if (j != SIZE - 1)
//             cout << string(1, ' ');
//     }
//     cout << "\n";

//     for (int margin = 0, i = 0, row = static_cast<int>('a'); i < SIZE; i++, row++)
//     {
//         cout << string(margin++, ' ');
//         cout << '|' << static_cast<char>(row) << '|' << string(1, ' ');
//         for (int j = 0; j < SIZE; j++)
//         {
//             Pair idx = std::make_pair(i, j);
//             Player p = g.GetNode(idx)->GetPlayer();
//             const char player_symbol = symbols[p];

//             cout << player_symbol;
//             if (j != SIZE - 1)
//                 cout << " - ";
//         }
//         cout << '\n';
//         if (i != SIZE - 1)
//         {
//             cout << string(margin++ + 4, ' ');
//             for (int j = 0; j < SIZE - 1; j++)
//             {
//                 cout << "\\ / ";
//             }
//             cout << "\\" << '\n';
//         }
//     }
// }

void Board::printGraphData() const
{
    cout << "Node # "
         << " Neighbours" << endl;
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            cout << left << setw(8) << g.GetNode(std::make_pair(i, j))->GetID();
            for (const auto neighbour : g.GetNode(std::make_pair(i, j))->GetNeighbours())
                cout << neighbour->GetID() << " ";
            cout << endl;
        }
    }
}

#endif // BOARD_H
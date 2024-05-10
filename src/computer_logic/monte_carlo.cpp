#include <iostream>
#include <random>
#include <vector>

#include "../../include/computer_logic/monte_carlo.hpp"
#include "../../include/utility.hpp"

using std::vector;

MonteCarlo::MonteCarlo(int nTrials) : _nTrials(nTrials) {}

// TODO: Major Refactor Monte Carlo code
// TODO: Add comments
Pair MonteCarlo::decideNextMove(const Graph &curGraph, const PlayerType curPlayerType) const
{
    // cout << "ADDRESS OF POINTERED GRAPH " << &curGraph << '\n';
    vector<Pair> avaiableMoves;
    _collectAvailableNodes(curGraph, avaiableMoves);
    // cout << "something wrong is happening\n";
    // cout << curGraph.GetSize() << " ";


    // Seed the random number generator
    std::random_device rd;
    std::mt19937 gen(42);

    int maxWins = 0;
    Pair maxWinsMove;
    const PlayerType otherPlayerType = (curPlayerType == PlayerType::PLAYER_1) ? PlayerType::PLAYER_2 : PlayerType::PLAYER_1;

    for (size_t i = 0; i < avaiableMoves.size(); i++)
    {
        Pair evalMove = avaiableMoves[i];
        int winsForEvalMove = 0;
        char pause;

        // for (auto moves : avaiableMoves)
        //     cout << moves << " ";
        // // cout << "\nEvaluating move" << evalMove << '\n';
        // for (auto neighbours : curGraph.GetNode(evalMove)->GetNeighbours())
        //     cout << neighbours->GetIDX() << " ";
        // cout << "Press y to continue: ";
        // cin >> pause;

        for (size_t trial = 0; trial < _nTrials; trial++)
        {
            // TODO: Check a way to use the same graph, maybe erasing the PlayerType field
            Graph simGraph(curGraph);
            simGraph.setPlayer(evalMove, curPlayerType); // make eval move by COMP
            // cout << "\nBack into the main loop " << simGraph.GetNode(evalMove) << " " << evalMove << " has " << simGraph.GetNode(evalMove)->GetPlayer() << '\n';

            vector<Pair> simAvailableMoves = avaiableMoves;
            simAvailableMoves.erase(simAvailableMoves.begin() + i); // remove evalMove from simulation

            while (!simAvailableMoves.empty())
            {
                _simulateNextMoveFromAvailableMoves(simGraph, simAvailableMoves, gen, curPlayerType);

                if (!simAvailableMoves.empty())
                    _simulateNextMoveFromAvailableMoves(simGraph, simAvailableMoves, gen, otherPlayerType);
            }
            // std::cout << "\x1B[2J\x1B[H"; // Clear screen
            // simGraph.printGraph();

            // node_set STARTS = GetStarts();
            // node_set GOALS = GetGoals();
            uspNode starts, goals;

            // TODO: make this modular (also this seems wrong). Maybe pass a board object instead of graph.
            for (int k = 0; k < simGraph.getSize(); k++)
            {
                Pair startIdx = std::make_pair(k, 0);
                Pair goalIdx = std::make_pair(k, simGraph.getSize() - 1);

                starts.insert(simGraph.getNode(startIdx));
                goals.insert(simGraph.getNode(goalIdx));
            }
            // Player playerType = GetPlayerType();
            // cout << "\n\ninside simulation loop function printing STARTS\n\n";
            // for (auto start : starts)
            //     cout << start << " " << start->GetIDX() << " has " << start->GetPlayer() << '\n';

            if (simGraph.isBridgeFormed(starts, goals, curPlayerType))
            {
                winsForEvalMove++;
                // cout << "\n\nComputer wins this round, total wins are: " << ++winsForEvalMove << '\n';
            }
        }
        if (winsForEvalMove > maxWins)
            {
                maxWins = winsForEvalMove;
                maxWinsMove = evalMove;
            }
        // cout << "Wins for move " << evalMove << " : " << winsForEvalMove << '\n';
        // cout << "Press y to continue: ";
        // cin >> pause;
        // cout << "\n\n";
    }
    std::cout << "\nSelected AI move: " << maxWinsMove;

    // char pause;
    // cout << "Press y to continue: ";
    // cin >> pause;

    return maxWinsMove;
}

void MonteCarlo::_simulateNextMoveFromAvailableMoves(Graph &g, vector<Pair> &availableMoves, std::mt19937 &gen, const PlayerType playerType) const
{
    // Generate a random index within the range of the vector
    // TODO: instead of random index can randomize once, since vector.erase might be taking longer time


    std::uniform_int_distribution<int> dis(0, availableMoves.size() - 1);
    int randIdx = dis(gen);
    Pair next_move = availableMoves[randIdx];
    
    availableMoves.erase(availableMoves.begin() + randIdx);
    g.setPlayer(next_move, playerType);
    // cout << "Now in simulation " << simGraph.GetNode(next_move) << " " << next_move << " has " << simGraph.GetNode(next_move)->GetPlayer() << '\n';
}

void MonteCarlo::_collectAvailableNodes(const Graph &curGraph, std::vector<Pair> &avaiableNodes) const
{
    // Collect all available nodes, can be optiizzed to maintain such a vector.
    for (size_t i = 0; i < curGraph.getSize(); i++)
    {
        for (size_t j = 0; j < curGraph.getSize(); j++)
        {
            Pair idx = std::make_pair(i, j);
            // cout << i << j << " ";
            if (curGraph.isAvailable(idx))
                avaiableNodes.push_back(idx);
        }
    }
    // cout << "Created available\n";
}
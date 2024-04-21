#include <iostream>
#include <vector>

#include "../../include/computer_logic/monte_carlo.hpp"
#include "../../include/utility.hpp"

using std::vector;

MonteCarlo::MonteCarlo(int nTrials) : _nTrials(nTrials) {}

// TODO: Major Refactor Monte Carlo code
// TODO: Add comments
Pair MonteCarlo::decideNextMove(const Graph &curGraph) const
{
    // cout << "ADDRESS OF POINTERED GRAPH " << &curGraph << '\n';
    vector<Pair> avaiableMoves;
    // cout << "something wrong is happening\n";
    // cout << curGraph.GetSize() << " ";

    // Collect all available nodes, can be optiizzed to maintain such a vector.
    for (size_t i = 0; i < curGraph.getSize(); i++)
    {
        for (size_t j = 0; j < curGraph.getSize(); j++)
        {
            Pair idx = std::make_pair(i, j);
            // cout << i << j << " ";
            if (curGraph.isAvailable(idx))
                avaiableMoves.push_back(idx);
        }
    }
    // cout << "Created available\n";
    // Seed the random number generator
    std::random_device rd;
    std::mt19937 gen(42);

    int maxWins = 0;
    Pair maxWinsMove;

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
            Graph simGraph(curGraph);
            simGraph.setPlayer(evalMove, PlayerType::PLAYER_2); // make eval move by COMP
            // cout << "\nBack into the main loop " << simGraph.GetNode(evalMove) << " " << evalMove << " has " << simGraph.GetNode(evalMove)->GetPlayer() << '\n';

            vector<Pair> simAvailableMoves = avaiableMoves;
            simAvailableMoves.erase(simAvailableMoves.begin() + i); // remove evalMove from simulation

            while (!simAvailableMoves.empty())
            {
                // Generate a random index within the range of the vector
                std::uniform_int_distribution<int> dis(0, simAvailableMoves.size() - 1);
                int randIdx = dis(gen);
                Pair next_move = simAvailableMoves[randIdx];
                simAvailableMoves.erase(simAvailableMoves.begin() + randIdx);
                simGraph.setPlayer(next_move, PlayerType::PLAYER_1);
                // cout << "Now in simulation " << simGraph.GetNode(next_move) << " " << next_move << " has " << simGraph.GetNode(next_move)->GetPlayer() << '\n';

                if (!simAvailableMoves.empty())
                {
                    std::uniform_int_distribution<int> dis(0, simAvailableMoves.size() - 1);
                    int randIdx = dis(gen);
                    Pair next_move = simAvailableMoves[randIdx];
                    simAvailableMoves.erase(simAvailableMoves.begin() + randIdx);
                    simGraph.setPlayer(next_move, PlayerType::PLAYER_2);
                    // cout << "Now in simulation " << simGraph.GetNode(next_move) << " " << next_move << " has " << simGraph.GetNode(next_move)->GetPlayer() << '\n';
                }
            }
            // std::cout << "\x1B[2J\x1B[H"; // Clear screen
            // simGraph.printGraph();

            // node_set STARTS = GetStarts();
            // node_set GOALS = GetGoals();
            uspNode starts, goals;

            // TODO: make this modular
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

            if (simGraph.isBridgeFormed(starts, goals, PlayerType::PLAYER_2))
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
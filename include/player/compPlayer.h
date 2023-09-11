#ifndef COMP_PLAYER
#define COMP_PLAYER

#include "IPlayer.h"
#include "../graph.h"

class CompPlayer : public IPlayer
{
    int NTRIALS;
    // Graph *curGraph;
    Pair MonteCarloMove(Graph &);
    Pair RandomMove(int);

public:
    CompPlayer(string name) : IPlayer(Player::COMP, name), NTRIALS(10) {}
    ~CompPlayer() {}
    Pair GetMove(Graph &) override;
    // void PassGraph(Graph &g) override;
};

Pair CompPlayer::MonteCarloMove(Graph &curGraph)
{
    cout << "ADDRESS OF POINTERED GRAPH " << &curGraph << '\n';
    vector<Pair> avaiableMoves;
    cout << "something wrong is happening\n";
    cout << curGraph.GetSize() << " ";

    // Collect all available nodes, can be optiizzed to maintain such a vector.
    for (size_t i = 0; i < curGraph.GetSize(); i++)
    {
        for (size_t j = 0; j < curGraph.GetSize(); j++)
        {
            Pair idx = std::make_pair(i, j);
            cout << i << j << " ";
            if (curGraph.IsAvailable(idx))
                avaiableMoves.push_back(idx);
        }
    }
    cout << "Created available\n";
    // Seed the random number generator
    std::random_device rd;
    std::mt19937 gen(rd());

    int maxWins = 0;
    Pair maxWinsMove;

    for (size_t i = 0; i < avaiableMoves.size(); i++)
    {
        Pair evalMove = avaiableMoves[i];
        int winsForEvalMove = 0;
        char pause;

        for (auto moves : avaiableMoves)
            cout << moves << " ";
        cout << "\nEvaluating move" << evalMove << '\n';
        for (auto neighbours : curGraph.GetNode(evalMove)->GetNeighbours()) cout << neighbours->GetIdx() << " ";
        cout << "Press y to continue: ";
        cin >> pause;

        for (size_t trial = 0; trial < NTRIALS; trial++)
        {
            Graph simGraph(curGraph);
            simGraph.SetPlayer(evalMove, Player::COMP); // make eval move by COMP

            vector<Pair> simAvailableMoves = avaiableMoves;
            simAvailableMoves.erase(simAvailableMoves.begin() + i); // remove evalMove from simulation

            while (!simAvailableMoves.empty())
            {
                // Generate a random index within the range of the vector
                std::uniform_int_distribution<int> dis(0, simAvailableMoves.size() - 1);
                int randIdx = dis(gen);
                Pair next_move = simAvailableMoves[randIdx];
                simAvailableMoves.erase(simAvailableMoves.begin() + randIdx);
                simGraph.SetPlayer(next_move, Player::HUMAN);

                if (!simAvailableMoves.empty())
                {
                    std::uniform_int_distribution<int> dis(0, simAvailableMoves.size() - 1);
                    int randIdx = dis(gen);
                    Pair next_move = simAvailableMoves[randIdx];
                    simAvailableMoves.erase(simAvailableMoves.begin() + randIdx);
                    simGraph.SetPlayer(next_move, Player::COMP);
                }
            }

            simGraph.printGraph();

            node_set STARTS = GetStarts();
            node_set GOALS = GetGoals();
            // Player playerType = GetPlayerType();

            if (simGraph.IsBridgeFormed(STARTS, GOALS, Player::COMP))
            {
                cout << "\n\nComputer wins this round, total wins are: " << ++winsForEvalMove << '\n';
            }

            cout << "Wins for this move: " << winsForEvalMove << '\n';
            cout << "Press y to continue: ";
            cin >> pause;
            cout << "\n\n";
            
            if (winsForEvalMove > maxWins)
            {
                maxWins = winsForEvalMove;
                maxWinsMove = evalMove;
            }
        }
    }
    cout << "Selected AI move: " << maxWinsMove;

    char pause;
    cout << "Press y to continue: ";
    cin >> pause;

    return maxWinsMove;
}

Pair CompPlayer::RandomMove(int SIZE)
{
    std::random_device rd;
    std::mt19937 gen(rd());

    // Define the range for the distribution
    std::uniform_int_distribution<> dis(0, SIZE - 1);

    // Generate a single random integer
    int row = dis(gen), col = dis(gen);

    return std::make_pair(row, col);
}

Pair CompPlayer::GetMove(Graph &g)
{
    return MonteCarloMove(g);
}

// void CompPlayer::PassGraph(Graph &g)
// {
//     cout << "Argyument after passing address: " << &g << '\n';
//     curGraph = &g;
//     cout << "curGraph graph address: " << curGraph << '\n';
//     std::cout << "Copied graph size : " << curGraph.GetSize() << "\n\n";
// }

#endif // COMP_PLAYER
/**
 * @file Graph.h
 * @author Rishabh Bhattacharya (ribhattacharya@ucsd.edu)
 * @brief
 * @version 0.1
 * @date 2023-Aug-10
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <random>
#include <cstdlib>
#include <iomanip>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <queue>

#include "Node.h"

using std::cin;
using std::cout;
using std::endl;
using std::left;
using std::mt19937;
using std::queue;
using std::random_device;
using std::right;
using std::setw;
using std::string;
using std::uniform_int_distribution;
using std::unordered_map;
using std::unordered_set;
using std::vector;

class Graph
{
    /*
    DESC: Graph class to create and process the graph.
    */
    const int SIZE;
    vector<vector<Node *>> nodes;
    unordered_map<Player, char> symbols = {
        {Player::HUMAN, 'X'},
        {Player::COMP, 'O'},
        {Player::NONE, '.'}};
    unordered_set<Node *> Human;
    unordered_set<Node *> Comp;
    unordered_set<Node *> None;

public:
    Graph(int);
    ~Graph();

    void createEdges();
    Node *getNode(int, int);

    void playGame();
    bool isValidMove(Node *);
    const Player checkWinner();

    Node *getHumanMove();
    void makeHumanMove();
    bool isHumanTarget(Node *);

    Node *getRandomMove();
    void makeComputerMove();
    bool isCompTarget(Node *);

    const char getPlayerSymbol(Player);
    void printGraph();
    void printGraphData();
};

/// @brief Construct graph of given size.
/// @param s Size of graph (s x s) to be consstructed.
Graph::Graph(int s) : SIZE(s), nodes(SIZE, vector<Node *>(SIZE))
{
    cout << "Initialized board with size = " << SIZE << ".\n"
         << endl;

    int num_nodes = 0;
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            nodes[i][j] = new Node(num_nodes++);
            None.insert(nodes[i][j]); // Insert all nodes to None initially
        }
    }

    createEdges();
    printGraph();
}

/// @brief Graph destructor, deletes all nodes.
Graph::~Graph()
{
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            nodes[i][j] = (delete nodes[i][j], nullptr);
}

/// @brief Create edges between all nodes.
void Graph::createEdges()
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            // 6 directions
            vector<vector<int>> directions{
                {i, j - 1},
                {i - 1, j},
                {i - 1, j + 1},
                {i, j + 1},
                {i + 1, j},
                {i + 1, j - 1}};

            vector<Node *> neighbours;
            for (const auto dir : directions)
            {
                int ii = dir[0], jj = dir[1];
                if (ii >= 0 && ii < SIZE && jj >= 0 && jj < SIZE)
                    neighbours.push_back(nodes[ii][jj]);
            }
            nodes[i][j]->setNeighbours(neighbours);
        }
    }
}

Node *Graph::getNode(int i, int j) { return nodes[i][j]; }

void Graph::playGame()
{
    while (true)
    {
        makeHumanMove();
        if (checkWinner() == Player::HUMAN)
        {
            cout << "Human Wins!\n";
            return;
        }

        makeComputerMove();
        if (checkWinner() == Player::COMP)
        {
            cout << "Computer Wins!\n";
            return;
        }
    }

    cout << "\nGame ends in a draw!" << endl;
    return;
}

bool Graph::isValidMove(Node *node)
{
    if (node->getPlayer() == Player::NONE)
        return true;

    cout << "Invalid move!\n";
    return false;
}

Node *Graph::getHumanMove()
{
    int row = 0, col = 0;
    cout << "Enter row (1-indexed): ";
    cin >> row;
    cout << "Enter column (1-indexed): ";
    cin >> col;

    // Convert 1-indexed rows and columns into 0-indexed
    return nodes[--row][--col];
}

void Graph::makeHumanMove()
{
    Node *played_node = getHumanMove();

    while (!isValidMove(played_node))
    {
        cout << "Try again!\n";
        played_node = getHumanMove();
    }

    played_node->setPlayer(Player::HUMAN);
    Human.insert(played_node);
    None.erase(played_node);

    system("clear");
    printGraph();
}

bool Graph::isHumanTarget(Node *node)
{
    for (size_t j = 0; j < SIZE; j++)
    {
        if (node == nodes[SIZE - 1][j])
        {
            return true;
        }
    }

    return false;
}

Node *Graph::getRandomMove()
{
    std::random_device rd;
    std::mt19937 gen(rd());

    // Define the range for the distribution
    std::uniform_int_distribution<> dis(1, SIZE);

    // Generate a single random integer
    int row = dis(gen);
    int col = dis(gen);

    return nodes[--row][--col];
}

void Graph::makeComputerMove()
{
    Node *played_node = getRandomMove();

    while (!isValidMove(played_node))
    {
        cout << "Try again!\n";
        played_node = getRandomMove();
    }

    played_node->setPlayer(Player::COMP);
    Comp.insert(played_node);
    None.erase(played_node);

    system("clear");
    printGraph();
}

bool Graph::isCompTarget(Node *node)
{
    for (size_t i = 0; i < SIZE; i++)
        if (node == nodes[i][SIZE - 1])
            return true;

    return false;
}

const Player Graph::checkWinner()
{
    // Human check
    for (int j = 0; j < SIZE; j++)
    {
        unordered_set<Node *> temp = Human;
        unordered_set<Node *> OPEN, CLOSED;

        Node *start = nodes[0][j];
        if (Human.find(start) != Human.end())
        {
            OPEN.insert(start);
            while (!OPEN.empty())
            {
                Node *node_to_expand = *(OPEN.begin());
                OPEN.erase(node_to_expand);
                CLOSED.insert(node_to_expand);

                if (isHumanTarget(node_to_expand))
                    return Player::HUMAN;

                for (Node *neighbour : node_to_expand->getNeighbours())
                {
                    if (Human.find(neighbour) != Human.end())
                    { // Skip if neighbour is closed already
                        if (CLOSED.find(neighbour) != CLOSED.end())
                            continue;

                        if (OPEN.find(neighbour) == OPEN.end())
                            OPEN.insert(neighbour);
                    }
                }
            }
        }
    }

    // Computer check
    for (int i = 0; i < SIZE; i++)
    {
        unordered_set<Node *> temp = Comp;
        unordered_set<Node *> OPEN, CLOSED;

        Node *start = nodes[i][0];
        if (Comp.find(start) != Comp.end())
        {
            OPEN.insert(start);
            while (!OPEN.empty())
            {
                Node *node_to_expand = *(OPEN.begin());
                OPEN.erase(node_to_expand);
                CLOSED.insert(node_to_expand);

                if (isCompTarget(node_to_expand))
                    return Player::COMP;

                for (Node *neighbour : node_to_expand->getNeighbours())
                {
                    if (Comp.find(neighbour) != Comp.end())
                    {
                        // Skip if neighbour is closed already
                        if (CLOSED.find(neighbour) != CLOSED.end())
                            continue;

                        if (OPEN.find(neighbour) == OPEN.end())
                            OPEN.insert(neighbour);
                    }
                }
            }
        }
    }

    return Player::NONE;
}

const char Graph::getPlayerSymbol(const Player p) { return symbols[p]; }

void Graph::printGraph()
{
    int margin = 0;
    for (int i = 0; i < SIZE; i++)
    {
        cout << string(margin++, ' ');
        for (int j = 0; j < SIZE; j++)
        {
            Player p = nodes[i][j]->getPlayer();
            const char player_symbol = getPlayerSymbol(p);

            if (j == SIZE - 1)
                cout << player_symbol;
            else
                cout << player_symbol << " - ";
        }
        cout << '\n';
        if (i != SIZE - 1)
        {
            cout << string(margin++, ' ');
            for (int j = 0; j < SIZE - 1; j++)
            {
                cout << "\\ / ";
            }
            cout << "\\" << '\n';
        }
    }
}

void Graph::printGraphData()
{
    cout << "Node # "
         << " Neighbours" << endl;
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            cout << left << setw(8) << nodes[i][j]->getID();
            for (const auto neighbour : nodes[i][j]->getNeighbours())
                cout << neighbour->getID() << " ";
            cout << endl;
        }
    }
}

#endif // GRAPH_H
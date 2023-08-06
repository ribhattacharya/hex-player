#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <vector>
#include <string>
#include <unordered_map>

using std::cin;
using std::cout;
using std::endl;
using std::left;
using std::right;
using std::setw;
using std::string;
using std::unordered_map;
using std::vector;

enum class Player
{
    HUMAN,
    COMP,
    NONE
};

class Node
{
    /*
    DESC: Create the nodes and helper functions.
    */
    const int ID;
    Player player;
    vector<Node *> neighbours;

public:
    Node(int identifier) : ID(identifier), player(Player::NONE), neighbours({}) {}

    const int getID() { return ID; }
    const vector<Node *> &getNeighbours() { return neighbours; }
    void setPlayer(Player p) { player = p; }
    const Player getPlayer() { return player; }
    void setNeighbours(vector<Node *> &neighbours) { this->neighbours = neighbours; }
};

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

public:
    Graph(int);
    ~Graph();

    void createEdges();
    Node *getNode(int, int);

    void playGame();
    void makeHumanMove();
    void makeComputerMove();
    const Player checkWinner();

    const char getPlayerSymbol(Player);

    void printGraph();
    void printGraphData();
};

Graph::Graph(int s) : SIZE(s), nodes(SIZE, vector<Node *>(SIZE))
{
    cout << "Initialized board with size = " << SIZE << ".\n"
         << endl;

    int num_nodes = 0;
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            nodes[i][j] = new Node(num_nodes++);

    createEdges();
    printGraph();
}

Graph::~Graph()
{
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            nodes[i][j] = (delete nodes[i][j], nullptr);
}

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
    int count = 2;
    while (count--)
    {
        makeHumanMove();
        // if (checkWinner() != Player::NONE)
        //     break;
        makeComputerMove();
        // if (checkWinner() != Player::NONE)
        //     break;
    }

    switch (checkWinner())
    {
    case Player::HUMAN:
        cout << "\nYou win!" << endl;
        break;

    case Player::COMP:
        cout << "\nComputer wins!" << endl;
        break;

    default:
        cout << "\nGame ends in a draw!" << endl;
        break;
    }
}

void Graph::makeHumanMove()
{
    int row = 0, col = 0;
    do
    {
        cout << "Your move!\n";
        cout << "Enter row (1-indexed): ";
        cin >> row;
        cout << "Enter column (1-indexed): ";
        cin >> col;

        // 1-indexed rows and columns into 0-indexed
        row--;
        col--;
    } while (nodes[row][col]->getPlayer() != Player::NONE);

    nodes[row][col]->setPlayer(Player::HUMAN);

    system("clear");
    printGraph();
}

void Graph::makeComputerMove()
{
    static int row = 4, col = 4;
    nodes[row--][col--]->setPlayer(Player::COMP);

    system("clear");
    printGraph();
}

const Player Graph::checkWinner()
{
    return Player::HUMAN;
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
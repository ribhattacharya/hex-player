#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <unordered_map>

using std::cout;
using std::endl;
using std::left;
using std::right;
using std::setw;
using std::unordered_map;
using std::vector;
using std::string;

enum class Player
{
    HUMAN,
    COMP,
    NONE
};

unordered_map<Player, char> symbols = {
    {Player::HUMAN, 'X'},
    {Player::COMP, 'O'},
    {Player::NONE, '.'}};

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
    Player getPlayer() { return player; }
    char getPlayerSymbol() { return symbols[player]; }
    void setNeighbours(vector<Node *> &neighbours) { this->neighbours = neighbours; }
};

class Graph
{
    /*
    DESC: Graph class to create and process the graph.
    */
    const int SIZE;
    vector<vector<Node *>> nodes;

public:
    Graph(int);
    ~Graph();

    void createEdges();
    Node *getNode(int, int);
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

void Graph::printGraph()
{
    int margin = 0;
    for (int i = 0; i < SIZE; i++)
    {
        cout << string(margin++, ' ');
        for (int j = 0; j < SIZE; j++)
        {
            if (j == SIZE - 1)
                cout << nodes[i][j]->getPlayerSymbol();
            else
                cout << nodes[i][j]->getPlayerSymbol() << " - ";
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

int main(int argc, char **argv)
{
    int board_size = 5;
    if (argc > 1)
    {
        try
        {
            board_size = std::stoi(argv[1]);
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error: Invalid board size argument! Should be an integer, given '" << argv[1] << "'.\n";
            return 1;
        }
    }

    Graph graph(board_size);
    graph.printGraph();
    return 0;
}

#endif // GRAPH_H
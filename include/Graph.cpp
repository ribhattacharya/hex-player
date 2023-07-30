#ifndef GRAPH_H
#define GRAPH_H

#include<iostream>
#include<vector>

using std::vector;
using std::cout;
using std::endl;

class Node {
    /*
    DESC: Create the nodes and helper functions.
    */
    const int ID;
    vector<Node*> neighbours;

public:
    Node(int identifier = -1): ID(identifier) {}
    
    const int getID () {return ID;}
    vector<Node*> getNeighbours() {return neighbours;}
    void setNeighbours(vector<Node*> neighbours) {this->neighbours = neighbours;}
};

class Graph {
    /*
    DESC: Graph class to create and process the graph.
    */
    const int SIZE;
    vector<vector<Node*> > nodes;

public:
    Graph(int s): SIZE(s), nodes(SIZE, vector<Node*>(SIZE)) {
        // Create vector of nodes
        int num_nodes = 0;
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                nodes[i][j] = new Node(num_nodes++);
        
        // Create edges
        num_nodes = 0;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                cout << "Node " << num_nodes++ << " : ";
                vector<vector<int> > directions {
                    {i, j-1}, {i-1, j}, {i-1, j+1}, 
                    {i, j+1}, {i+1, j}, {i+1, j-1}
                };
                
                for (auto dir : directions) {
                    int ii = dir[0], jj = dir[1];
                    vector<Node*> neighbours;
                    
                    if (ii >= 0 && ii < SIZE && jj >= 0 && jj < SIZE){
                        neighbours.push_back(nodes[ii][jj]);
                        // cout << "(" << ii << "," << jj << "), "; 
                    }
                    nodes[i][j]->setNeighbours(neighbours);
                    for (auto neighbour: nodes[i][j]->getNeighbours())
                        cout << neighbour->getID() << " ";
                }
                cout << endl;
            }
        }
        cout << "Contructor invoked!" << endl;
    }

    void printGraph() {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                auto neighbours = nodes[i][j]->getNeighbours();
                cout << "Node " << nodes[i][j]->getID() << ": " << nodes[i][j]->getNeighbours().size();
                for (auto neighbour :neighbours)
                    cout << neighbour->getID() << " ";
                cout << endl;
            }
        }
    }
};

int main(int argc, char** argv) {
    Graph graph(5);
    graph.printGraph();
    return 0;
}

#endif // GRAPH_H
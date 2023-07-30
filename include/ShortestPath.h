#ifndef SHORTESTPATH_H
#define SHORTESTPATH_H

#include<iostream>
#include<iomanip>
#include<vector>
#include<string>
#include<limits>
#include<stack>
#include<queue>
#include<unordered_set>

#include "Graph.h"
#include "PriorityQueue.h"

using namespace std;




class ShortestPath {
    /*
    DESC: Implements the shortest path algorithm and processes the data to compute paths anhd distances.
    */
    const int start;
    const int goal;
    Graph G;
    
    vector<Node> nodes;
    vector<vector<int> > paths;
    unordered_set<int> CLOSED;
    PriorityQueue OPEN;
    double avg;
public:
    ShortestPath(int source_node, int target_node, Graph& graph) 
        : start(source_node), goal(target_node), G(graph), paths(vector<vector<int> >(graph.getNumNodes())){
            for (int i = 0; i < graph.getNumNodes(); i++)
                nodes.push_back(Node(i, (i == source_node)? 0 : INT_MAX));
            // G.printGraphAsList();
            
            runDijkstra();
        }
    
    void runDijkstra() {
        /*
        DESC: Main function calling other functions.
        */
        dijkstra();
        computePaths();
        computeAverageDist();
        printResults();
    }

    void dijkstra() {
        /*
        DESC: Runs dijkstra's algorithm on the given graph and start/goal nodes.
        */
        OPEN.push(start, 0);
        
        while (!OPEN.empty()) {
            
            int node_to_expand = OPEN.top().first;
            int cost_from_start = OPEN.top().second;
            OPEN.pop();
            CLOSED.insert(node_to_expand);
            
            vector<int> neighbours = G.getNeighbours(node_to_expand);
            for (int neighbour : neighbours) {
                // Shortest path start -> neighbour already found if it is CLOSED.
                if (CLOSED.find(neighbour) != CLOSED.end()) continue;
                
                // Check if current cost to neighbour (start -> node_to_expand -> neighbour) 
                // is better than the existing cost (start -> neighbour)
                bool cost_changed = false;
                int g = cost_from_start + G.getCost(node_to_expand, neighbour);
                if (g < nodes[neighbour].getCostFromStart()) {
                    nodes[neighbour].setCostFromStart(g);           // update cost
                    nodes[neighbour].setPrevNode(node_to_expand);   // update parent
                    cost_changed = true;
                };             
                
                // If neighbour is not in OPEN, then add it. If it IS in OPEN, 
                // then update priority only if it has been changed. 
                // This would save us unnecessary push and pop from heap.
                if (OPEN.contains(neighbour)) {
                    if (cost_changed)
                        OPEN.changePriority(neighbour, nodes[neighbour].getCostFromStart());
                }
                else
                    OPEN.push(neighbour, nodes[neighbour].getCostFromStart());
            }
        }
        return;
    }

    void computePaths() {
        /*
        DESC: Compute paths by backtracking the previous nodes within each node.
        */
        for (int i = 0; i < G.getNumNodes(); i++) {
            int prev_node = i;
            stack<int> path;
            
            while(prev_node != -1) {
                path.push(prev_node);
                prev_node = nodes[prev_node].getPrevNode();
            }
            while (!path.empty()) {
                paths[i].push_back(path.top());
                path.pop();
            }
        } 
    }

    double computeAverageDist() {
        /*
        DESC: Return the average distance between start and all other nodes.

        OUTPUTS:
            double avg: Average distance
        */
        int count = 0;
        for (int i = 0; i < G.getNumNodes(); i++)
            if (i != start && nodes[i].getCostFromStart() < INT_MAX) // Skip the disconnected and start node
                avg += static_cast<double>(nodes[i].getCostFromStart() - avg) / ++count;

        return avg;
    }

    void printResults() {
        /*
        DESC: Print all the results.
                1. Shortest distances from start -> each node
                2. Paths from start -> each node 
                3. Is path found from start to goal? (Yes/No)
                4. Average distance from start to any other node in the graph.
        */
        
        // 1. Shortest distances from start -> each node
        // 2. Paths from start -> each node 
        cout << '\n' << string(20, '-') << "Computed paths" << string(20, '-') << '\n';

        for (int i = 0; i < G.getNumNodes(); i++){
            cout << "dist(" << setw(2) << left << start << " -> " << setw(2) << right << i << ") = "
                 << setw(10) << left << nodes[i].getCostFromStart() << ": ";
            for(int j = 0; j < paths[i].size(); j++) {
                cout << setw(2) << right << paths[i][j];
                if (j < paths[i].size() - 1) cout << " -> ";
            }
            cout << "\n";
        }

        // 3. Is path found from start to goal? (Yes/No)
        // 4. Average distance from start to any other node in the graph.
        cout << "\nPath found from " << start << " to " << goal << "? "
             << ((nodes[goal].getCostFromStart() < INT_MAX)? "Yes." : "No.")
             << " Average distance between two nodes is " << avg << ".\n";
        
    }
};

#endif // SHORTESTPATH_H
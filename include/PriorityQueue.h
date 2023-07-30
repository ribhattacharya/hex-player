#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include<iostream>
#include<iomanip>
#include<vector>
#include<string>
#include<limits>
#include<queue>
#include<unordered_set>

using namespace std;

typedef pair<int, int> Pair;

class PriorityQueue {
    /*
    DESC: Implement the priority queue to be used for expanding the closest nodes.
    */
    priority_queue<Pair> pq;
    unordered_set<int> current;

public:
    PriorityQueue() {}

    void push(int node, int priority) {
        /*
        DESC: Push into the heap. C++ maintains a maxheap by default, with the priority being the first element.

        INPUTS:
            int node: node.
            int priority: priority.
        */
        pq.push(make_pair(-priority, node)); 
        current.insert(node); // Add the node to a set to facilitate PriorityQueue::contains().
    }

    void changePriority(int node, int priority) {
        /*
        DESC: Changes the priority of a given node.

        INPUTS:
            int node: node.
            int priority: priority.
        */
        priority_queue<Pair> temp;

        // Pop from the heap till the node is found, then push with modified priority.
        while(!pq.empty()) {
            if (pq.top().second == node) {
                pq.pop();
                pq.push(make_pair(-priority, node));
                break;
            }
            temp.push(pq.top());
            pq.pop();            
        }

        // Push back into the heap.
        while (!temp.empty()) {
            pq.push(temp.top());
            temp.pop();
        }
    }
    
    Pair top() {return make_pair(pq.top().second, -pq.top().first);}
    void pop() {int node = pq.top().second; pq.pop(); current.erase(node);}
    int size() {return pq.size();}
    bool empty() {return pq.empty();}
    bool contains(int node) {return current.find(node) != current.end();}
};

#endif // PRIORITYQUEUE_H
#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <stack>
using namespace std;

// Struct for representing a delivery route (edge)
struct Edge {
    string src, dest;  // Distribution centers
    int time;          // Travel time in hours
};

// Alias for adjacency list entries
typedef pair<string, int> Pair;

// Graph class for the package delivery network
class Graph {
public:
    unordered_map<string, vector<Pair>> adjList;  // Adjacency list for centers

    // Graph constructor
    Graph(vector<Edge> const &edges) {
        for (auto &edge : edges) {
            adjList[edge.src].push_back({edge.dest, edge.time});
            adjList[edge.dest].push_back({edge.src, edge.time});  // Undirected graph
        }
    }

    // Print the graph's adjacency list
    void printGraph() {
        cout << "Package Delivery Network:" << endl;
        for (auto &node : adjList) {
            cout << node.first << " --> ";
            for (auto &neighbor : node.second) {
                cout << "(" << neighbor.first << ", " << neighbor.second << " hours) ";
            }
            cout << endl;
        }
    }

    // Perform Depth-First Search (DFS)
    void DFS(string start) {
        unordered_map<string, bool> visited;
        stack<string> s;

        s.push(start);

        cout << "DFS starting from " << start << ": ";
        while (!s.empty()) {
            string center = s.top();
            s.pop();

            if (!visited[center]) {
                visited[center] = true;
                cout << center << " ";
            }

            for (auto &neighbor : adjList[center]) {
                if (!visited[neighbor.first]) {
                    s.push(neighbor.first);
                }
            }
        }
        cout << endl;
    }

    // Perform Breadth-First Search (BFS)
    void BFS(string start) {
        unordered_map<string, bool> visited;
        queue<string> q;

        q.push(start);
        visited[start] = true;

        cout << "BFS starting from " << start << ": ";
        while (!q.empty()) {
            string center = q.front();
            q.pop();

            cout << center << " ";

            for (auto &neighbor : adjList[center]) {
                if (!visited[neighbor.first]) {
                    q.push(neighbor.first);
                    visited[neighbor.first] = true;
                }
            }
        }
        cout << endl;
    }
};

int main() {
    // Define the package delivery network (distribution centers and direct routes)
    vector<Edge> edges = {
        {"Center 1", "Center 2", 2}, {"Center 1", "Center 3", 4}, {"Center 2", "Center 4", 1},
        {"Center 3", "Center 4", 3}, {"Center 3", "Center 5", 6}, {"Center 4", "Center 5", 2},
        {"Center 2", "Center 6", 5}, {"Center 5", "Center 6", 4}
    };

    // Create the graph
    Graph graph(edges);

    // Print the graph
    graph.printGraph();

    // Perform DFS starting from Center 1
    graph.DFS("Center 1");

    // Perform BFS starting from Center 1
    graph.BFS("Center 1");

    return 0;
}

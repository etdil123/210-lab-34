#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

// Updated graph size to accommodate all nodes (0 to 11)
const int SIZE = 9;

struct Edge {
    int src, dest, weight;
};

typedef pair<int, int> Pair;

class Graph {
public:
    vector<vector<Pair>> adjList;

    Graph(vector<Edge> const &edges) {
        adjList.resize(SIZE);

        for (auto &edge: edges) {
            int src = edge.src;
            int dest = edge.dest;
            int weight = edge.weight;

            // Ensure the edge references valid nodes
            if (src >= SIZE || dest >= SIZE || src < 0 || dest < 0) {
                cerr << "Invalid edge: (" << src << ", " << dest << ")" << endl;
                continue;
            }

            adjList[src].push_back(make_pair(dest, weight));
            adjList[dest].push_back(make_pair(src, weight));  // For undirected graph
        }
    }

    void printGraph() {
        cout << "Graph's adjacency list:" << endl;
        for (int i = 0; i < adjList.size(); i++) {
            cout << i << " --> ";
            for (Pair v : adjList[i])
                cout << "(" << v.first << ", " << v.second << ") ";
            cout << endl;
        }
    }

    void DFS(int start) {
        vector<bool> visited(SIZE, false);
        stack<int> s;

        s.push(start);

        cout << "DFS starting from node " << start << ": ";
        while (!s.empty()) {
            int v = s.top();
            s.pop();

            if (!visited[v]) {
                visited[v] = true;
                cout << v << " ";
            }

            for (auto &neighbor : adjList[v]) {
                if (!visited[neighbor.first]) {
                    s.push(neighbor.first);
                }
            }
        }
        cout << endl;
    }

    void BFS(int start) {
        vector<bool> visited(SIZE, false);
        queue<int> q;

        q.push(start);
        visited[start] = true;

        cout << "BFS starting from node " << start << ": ";
        while (!q.empty()) {
            int v = q.front();
            q.pop();

            cout << v << " ";

            for (auto &neighbor : adjList[v]) {
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
    // Updating the graph by deleting two nodes and adding 6 nodes
    vector<Edge> edges = {
        {0, 1, 10}, {0, 2, 15}, {0, 4, 20},
        {1, 5, 25}, {2, 4, 30}, {2, 7, 12},
        {4, 8, 18}, {5, 3, 22}, {7, 8, 14},
        {8, 9, 35}, {7, 10, 19}, {6, 10, 24},
        {8, 6, 17}, {9, 11, 20}
    };

    // Creates the graph
    Graph graph(edges);

    // Prints adjacency list
    graph.printGraph();

    // Perform DFS starting from node 0
    graph.DFS(0);

    // Perform BFS starting from node 0
    graph.BFS(0);

    return 0;
}

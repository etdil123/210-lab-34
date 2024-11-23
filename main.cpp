#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <stack>
#include <climits> // For INT_MAX
using namespace std;

// Struct for representing a delivery route (edge)
struct Edge {
    string src, dest;  // Distribution centers
    int weight;        // Route weight (e.g., travel time in hours)
};

// Graph class for the package delivery network
class Graph {
public:
    unordered_map<string, vector<pair<string, int>>> adjList;  // Adjacency list

    // Constructor to build the graph
    Graph(vector<Edge> const &edges) {
        for (auto &edge : edges) {
            adjList[edge.src].push_back({edge.dest, edge.weight});
            adjList[edge.dest].push_back({edge.src, edge.weight});  // Undirected graph
        }
    }

    // Display the adjacency list
    void displayGraph() {
        cout << "Package Delivery Network (Adjacency List):\n";
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
            string current = s.top();
            s.pop();

            if (!visited[current]) {
                visited[current] = true;
                cout << current << " ";
            }

            for (auto &neighbor : adjList[current]) {
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
            string current = q.front();
            q.pop();

            cout << current << " ";

            for (auto &neighbor : adjList[current]) {
                if (!visited[neighbor.first]) {
                    q.push(neighbor.first);
                    visited[neighbor.first] = true;
                }
            }
        }
        cout << endl;
    }

    // Find shortest paths using Dijkstra's Algorithm
    void findShortestPaths(string start) {
        unordered_map<string, int> distances; // Stores shortest distances
        for (auto &node : adjList) {
            distances[node.first] = INT_MAX; // Initialize distances to infinity
        }
        distances[start] = 0;

        // Min-heap priority queue: (distance, node)
        priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;
        pq.push({0, start});

        while (!pq.empty()) {
            int currentDistance = pq.top().first;
            string currentNode = pq.top().second;
            pq.pop();

            for (auto &neighbor : adjList[currentNode]) {
                string nextNode = neighbor.first;
                int edgeWeight = neighbor.second;

                if (currentDistance + edgeWeight < distances[nextNode]) {
                    distances[nextNode] = currentDistance + edgeWeight;
                    pq.push({distances[nextNode], nextNode});
                }
            }
        }

        // Print shortest paths
        cout << "\nShortest Paths from " << start << ":\n";
        for (auto &node : distances) {
            cout << node.first << ": ";
            if (node.second == INT_MAX) {
                cout << "Unreachable\n";
            } else {
                cout << node.second << " hours\n";
            }
        }
    }

    // Find the Minimum Spanning Tree (Prim's Algorithm)
    void findMST(string start) {
        unordered_map<string, bool> inMST;  // Tracks if a node is in the MST
        unordered_map<string, int> key;    // Minimum edge weight for each node
        unordered_map<string, string> parent; // Parent nodes to reconstruct the MST

        for (auto &node : adjList) {
            key[node.first] = INT_MAX; // Initialize all keys as infinity
        }
        key[start] = 0; // Start node has key 0

        // Min-heap priority queue: (weight, node)
        priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;
        pq.push({0, start});

        while (!pq.empty()) {
            string currentNode = pq.top().second;
            pq.pop();

            if (inMST[currentNode]) continue;
            inMST[currentNode] = true; // Include node in MST

            for (auto &neighbor : adjList[currentNode]) {
                string nextNode = neighbor.first;
                int edgeWeight = neighbor.second;

                // Update key and parent if a smaller edge is found
                if (!inMST[nextNode] && edgeWeight < key[nextNode]) {
                    key[nextNode] = edgeWeight;
                    parent[nextNode] = currentNode;
                    pq.push({edgeWeight, nextNode});
                }
            }
        }

        // Print the MST
        cout << "\nMinimum Spanning Tree (MST):\n";
        int totalWeight = 0;
        for (auto &node : parent) {
            cout << node.second << " -- " << node.first << " (" << key[node.first] << " hours)\n";
            totalWeight += key[node.first];
        }
        cout << "Total Weight of MST: " << totalWeight << " hours\n";
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

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Display Package Delivery Network\n";
        cout << "2. View package delivery (DFS)\n";
        cout << "3. Plan delivery route (BFS)\n";
        cout << "4. Calculate Shortest Delivery Time\n";
        cout << "5. Find Minimum Spanning Tree\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        
        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                graph.displayGraph();
                break;
            case 2:
                graph.DFS("Center 1");
                break;
            case 3:
                graph.BFS("Center 1");
                break;
            case 4:
                graph.findShortestPaths("Center 1");
                break;
            case 5:
                graph.findMST("Center 1");
                break;
            case 6:
                cout << "Exiting program. Goodbye!\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}

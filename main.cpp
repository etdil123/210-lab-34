#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <climits> // For INT_MAX
using namespace std;

// Struct for representing a delivery route (edge)
struct Edge {
    string src, dest;  // Distribution centers
    int weight;        // Route weight (e.g., travel time in hours)
};

// Alias for adjacency list entries
typedef pair<int, string> Pair; // (weight, node)

// Graph class for the package delivery network
class Graph {
public:
    unordered_map<string, vector<pair<string, int>>> adjList;  // Adjacency list for centers

    // Graph constructor
    Graph(vector<Edge> const &edges) {
        for (auto &edge : edges) {
            adjList[edge.src].push_back({edge.dest, edge.weight});
            adjList[edge.dest].push_back({edge.src, edge.weight});  // Undirected graph
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

    // Find the Minimum Spanning Tree (Prim's Algorithm)
    void findMST(string start) {
        unordered_map<string, bool> inMST;  // Tracks if a node is in the MST
        unordered_map<string, string> parent; // Tracks parent nodes for the MST
        unordered_map<string, int> key;   // Minimum edge weight for each node

        for (auto &node : adjList) {
            key[node.first] = INT_MAX; // Initialize all keys as infinity
        }
        key[start] = 0; // Start node has key 0

        // Min-heap priority queue: (weight, node)
        priority_queue<Pair, vector<Pair>, greater<Pair>> pq;
        pq.push({0, start});

        while (!pq.empty()) {
            string currentNode = pq.top().second;
            pq.pop();

            if (inMST[currentNode]) {
                continue; // Skip if already in MST
            }
            inMST[currentNode] = true; // Include the node in MST

            // Explore neighbors
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
        cout << "Total weight of MST: " << totalWeight << " hours\n";
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

    // Find the Minimum Spanning Tree
    graph.findMST("Center 1");

    return 0;
}

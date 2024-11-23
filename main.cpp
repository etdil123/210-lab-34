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
    int time;          // Travel time in hours
};

// Alias for adjacency list entries
typedef pair<int, string> Pair; // (distance, node)

// Graph class for the package delivery network
class Graph {
public:
    unordered_map<string, vector<pair<string, int>>> adjList;  // Adjacency list for centers

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

    // Find shortest path using Dijkstra's algorithm
    void findShortestPath(string start) {
        unordered_map<string, int> distances; // Stores shortest distances to each node
        unordered_map<string, string> previous; // Tracks the previous node in the path
        for (auto &node : adjList) {
            distances[node.first] = INT_MAX; // Initialize distances as infinite
        }
        distances[start] = 0;

        // Min-heap priority queue: (distance, node)
        priority_queue<Pair, vector<Pair>, greater<Pair>> pq;
        pq.push({0, start}); // Push initial node with distance 0

        while (!pq.empty()) {
            Pair top = pq.top();  // Extract top element
            pq.pop();

            int currentDistance = top.first; // Distance of the current node
            string currentNode = top.second; // Node being processed

            // Process neighbors
            for (auto &neighbor : adjList[currentNode]) {
                string nextNode = neighbor.first;
                int edgeWeight = neighbor.second;

                int newDistance = currentDistance + edgeWeight;
                if (newDistance < distances[nextNode]) {
                    distances[nextNode] = newDistance;
                    previous[nextNode] = currentNode;
                    pq.push({newDistance, nextNode});
                }
            }
        }

        // Print shortest distances
        cout << "\nShortest Path Distances from " << start << ":\n";
        for (auto &node : distances) {
            cout << node.first << " - " << (node.second == INT_MAX ? "Unreachable" : to_string(node.second) + " hours") << endl;
        }

        // Print paths to each node
        cout << "\nPaths from " << start << ":\n";
        for (auto &node : distances) {
            if (node.second != INT_MAX) {
                string path = node.first;
                string current = node.first;
                while (previous.find(current) != previous.end()) {
                    current = previous[current];
                    path = current + " -> " + path;
                }
                cout << path << " (" << node.second << " hours)\n";
            }
        }
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

    // Find shortest paths from Center 1
    graph.findShortestPath("Center 1");

    return 0;
}

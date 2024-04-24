#include <iostream>
#include <queue>
#include <vector>
#include <omp.h>

using namespace std;

// Function to perform BFS using OpenMP and search for a specific node
bool bfs_openmp(const vector<vector<int>>& graph, int start, int target, vector<bool>& visited) {
    queue<int> q;
    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        // If the current node is the target node, return true (found)
        if (current == target) {
            return true;
        }

        // Process neighbors of the current node
        #pragma omp parallel for
        for (int i = 0; i < graph[current].size(); ++i) {
            int neighbor = graph[current][i];
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }

    // Target node not found
    return false;
}

int main() {
    int num_nodes, num_edges;
    cout << "Enter the number of nodes: ";
    cin >> num_nodes;
    cout << "Enter the number of edges: ";
    cin >> num_edges;

    // Create adjacency list representation of the graph
    vector<vector<int>> graph(num_nodes);

    cout << "Enter edges (node u, node v):" << endl;
    for (int i = 0; i < num_edges; ++i) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u); // Assuming undirected graph
    }

    int target_node;
    cout << "Enter the target node to search for: ";
    cin >> target_node;

    vector<bool> visited(num_nodes, false);

    // Perform BFS from each unvisited node
    bool found = false;
    for (int i = 0; i < num_nodes; ++i) {
        if (!visited[i]) {
            found = bfs_openmp(graph, i, target_node, visited);
            if (found) {
                break; // Stop if target node is found
            }
        }
    }

    if (found) {
        cout << "Node " << target_node << " is reachable!" << endl;
    } else {
        cout << "Node " << target_node << " is not reachable." << endl;
    }

    return 0;
}

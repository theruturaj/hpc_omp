#include <iostream>
#include <queue>
#include <vector>
#include <omp.h>

using namespace std;

// Function to perform BFS using OpenMP
void bfs_openmp(const vector<vector<int>>& graph, int start, vector<bool>& visited) {
    queue<int> q;
    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        #pragma omp parallel for
        for (int i = 0; i < graph[current].size(); ++i) {
            int neighbor = graph[current][i];
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
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

    vector<bool> visited(num_nodes, false);

    // Perform BFS from each unvisited node
    for (int i = 0; i < num_nodes; ++i) {
        if (!visited[i]) {
            bfs_openmp(graph, i, visited);
        }
    }

    // Output the visited nodes
    cout << "Visited nodes:" << endl;
    for (int i = 0; i < num_nodes; ++i) {
        if (visited[i]) {
            cout << i << " ";
        }
    }
    cout << endl;

    return 0;
}


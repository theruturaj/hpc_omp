#include <iostream>
#include <vector>
#include <omp.h>
using namespace std;

const int MAXN = 1e5;
vector<int> adj[MAXN+5]; // adjacency list
bool visited[MAXN+5]; // mark visited nodes

void dfs(int node) {
    visited[node] = true;
    #pragma omp parallel for
    for (int i = 0; i < adj[node].size(); i++) {
        int next_node = adj[node][i];
        if (!visited[next_node]) {
            dfs(next_node);
        }
    }
}

bool searchNode(int node, int target) {
    visited[node] = true;
    if (node == target) {
        return true; // Found the target node
    }
    
    bool found = false;
    #pragma omp parallel for reduction(||:found)
    for (int i = 0; i < adj[node].size(); i++) {
        int next_node = adj[node][i];
        if (!visited[next_node]) {
            found = found || searchNode(next_node, target);
        }
    }
    
    return found;
}

int main() {
    cout << "Please enter number of nodes and edges: ";
    int n, m; // number of nodes and edges
    cin >> n >> m;

    cout << "Please enter the edges (u v):" << endl;
    for (int i = 0; i < m; i++) {
        int u, v; // edge between u and v
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int start_node; // start node of DFS
    cout << "Enter the start node for DFS: ";
    cin >> start_node;

    int target_node; // node to search for
    cout << "Enter the target node to search for: ";
    cin >> target_node;

    // Perform DFS from the start_node to mark visited nodes
    dfs(start_node);

    // Check if the target_node is reachable from the start_node
    bool found = searchNode(start_node, target_node);

    if (found) {
        cout << "Node " << target_node << " is reachable from node " << start_node << endl;
    } else {
        cout << "Node " << target_node << " is not reachable from node " << start_node << endl;
    }

    return 0;
}


//Number of nodes (n): 6
//Number of edges (m): 5

//edges - 1 2
//1 3
//2 4
//2 5
//3 6
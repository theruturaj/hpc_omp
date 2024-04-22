#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>
using namespace std;

class Graph
{
    int V;
    vector<vector<int>> adj;
public:
    Graph(int V) : V(V), adj(V) {}

    void addEdge(int v, int w)
    {
        adj[v].push_back(w);
    }

    void parallelDFS(int startVertex)
    {
        vector<bool> visited(V, false);
        parallelDFSUtil(startVertex, visited);
    }

    void parallelDFSUtil(int v, vector<bool> &visited)
    {
        visited[v] = true;
        cout << v << " ";
        for (int i = 0; i < adj[v].size(); ++i)
        {
            int n = adj[v][i];
            if (!visited[n])
                parallelDFSUtil(n, visited);
        }
    }

    void parallelBFS(int startVertex)
    {
        vector<bool> visited(V, false);
        queue<int> q;
        visited[startVertex] = true;
        q.push(startVertex);
        while (!q.empty())
        {
            int v = q.front();
            q.pop();
            cout << v << " ";
            for (int i = 0; i < adj[v].size(); ++i)
            {
                int n = adj[v][i];
                if (!visited[n])
                {
                    visited[n] = true;
                    q.push(n);
                }
            }
        }
    }
};

int main()
{
    int V, E; // Number of vertices and edges
    cout << "Enter the number of vertices: ";
    cin >> V;
    Graph g(V);

    cout << "Enter the number of edges: ";
    cin >> E;

    cout << "Enter the edges (format: source destination):" << endl;
    for (int i = 0; i < E; ++i)
    {
        int source, destination;
        cin >> source >> destination;
        g.addEdge(source, destination);
    }

    int startVertex;
    cout << "Enter the start vertex for DFS: ";
    cin >> startVertex;
    cout << "Depth-First Search (DFS): ";
    g.parallelDFS(startVertex);
    cout << endl;

    cout << "Enter the start vertex for BFS: ";
    cin >> startVertex;
    cout << "Breadth-First Search (BFS): ";
    g.parallelBFS(startVertex);
    cout << endl;

    return 0;
}

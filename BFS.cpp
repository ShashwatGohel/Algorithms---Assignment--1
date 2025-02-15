#include<bits/stdc++.h>
using namespace std;
struct Node {
    int color; // 0 = White, 1 = Gray, 2 = Black
    int d;
    int pi;
};
class Graph {
public:
    int V;
    vector<vector<int>> adj;
    vector<Node> nodes;
    Graph(int V) {
        this->V = V;
        adj.resize(V);
        nodes.resize(V);
    }
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u); // Assuming an undirected graph
    }
    void BFS(int s) {
        for (int u = 0; u < V; u++) {
            nodes[u].color = 0; // White
            nodes[u].d = numeric_limits<int>::max();
            nodes[u].pi = -1;
        }
        
        nodes[s].color = 1; // Gray
        nodes[s].d = 0;
        nodes[s].pi = -1;
        
        queue<int> q;
        q.push(s);
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            
            for (int v : adj[u]) {
                if (nodes[v].color == 0) { // White
                    nodes[v].color = 1; // Gray
                    nodes[v].d = nodes[u].d + 1;
                    nodes[v].pi = u;
                    q.push(v);
                }
            }
            
            nodes[u].color = 2; // Black
        }
    }
    
    void printResult() {
        for (int i = 0; i < V; i++) {
            cout << "Vertex " << i << ": Distance = " << nodes[i].d << ", Parent = " << nodes[i].pi << endl;
        }
    }
};

int main() {
    Graph g(6);
    g.addEdge(0, 1);
    g.addEdge(0, 3);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 5);
    int startVertex = 0;
    g.BFS(startVertex);
    g.printResult();
    return 0;
}

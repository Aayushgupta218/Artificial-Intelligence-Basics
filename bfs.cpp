#include <bits/stdc++.h>
using namespace std;

void bfs(vector<vector<int>>& adjMatrix, int start, vector<bool>& visited) {
    queue<int> q;
    visited[start] = true;
    q.push(start);
    
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        cout << node << " ";
        
        for (int i = 0; i < adjMatrix[node].size(); ++i) {
            if (adjMatrix[node][i] == 1 && !visited[i]) {
                q.push(i);
                visited[i] = true;
            }
        }
    }
}

int main() {
    int n;
    cout << "Enter the number of nodes: ";
    cin >> n;
    
    vector<vector<int>> adjMatrix(n, vector<int>(n, 0));
    vector<bool> visited(n, false);
    
    int e;
    cout << "Enter the number of edges: ";
    cin >> e;
    
    int v1, v2;
    for (int i = 0; i < e; ++i) {
        cout << "Enter the vertices between which the edge exists: ";
        cin >> v1 >> v2;
        adjMatrix[v1][v2] = 1;
        adjMatrix[v2][v1] = 1;
    }
    
    cout << "Adjacency Matrix:" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << adjMatrix[i][j] << " ";
        }
        cout << endl;
    }
    
    int start;
    cout << "Enter the starting node for BFS: ";
    cin >> start;
    
    bfs(adjMatrix, start, visited);
    cout << endl;
    
    return 0;
}

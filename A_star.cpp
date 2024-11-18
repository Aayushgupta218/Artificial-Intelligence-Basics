#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <climits>
using namespace std;

void DFS(const vector<vector<int>>& matrix, int start) {
    stack<int> s;
    vector<bool> visited(matrix.size(), false); 
    cout << "DFS order: ";
    s.push(start);

    while (!s.empty()) {
        int node = s.top();
        s.pop();

        if (!visited[node]) {
            cout << node << " ";
            visited[node] = true;

            for (int i = 0; i < matrix.size(); i++) { 
                if (matrix[node][i] != 0 && !visited[i]) {
                    s.push(i);
                }
            }
        }
    }
    cout << endl;
}

void BFS(const vector<vector<int>>& matrix, int start) {
    queue<int> q;
    vector<bool> visited(matrix.size(), false); 

    cout << "BFS order: ";
    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        cout << node << " ";

        for (int i = 0; i < matrix.size(); i++) {
            if (matrix[node][i] != 0 && !visited[i]) {
                q.push(i);
                visited[i] = true;
            }
        }
    }
    cout << endl;
}


void DLS(vector<vector<int>> matrix, int node, int depth, vector<bool>& visited) {    // Depth limited search
    if (depth == 0) {
        return;
    }

    visited[node] = true;
    cout << node << " ";

    for (int i = 0; i < matrix.size(); i++) {
        if (matrix[node][i] != 0 && !visited[i]) {
            DLS(matrix, i, depth - 1, visited);
        }
    }
}

void IDS(vector<vector<int>> matrix, int start) {
    int max_depth = 5; 
    for (int depth = 0; depth <= max_depth; depth++) {
        cout << "Depth " << depth << ": ";
        vector<bool> visited(matrix.size(), false);
        DLS(matrix, start, depth, visited);
        cout << endl;
    }
}

void BestFirstSearch(const vector<vector<int>>& matrix, int start) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<bool> visited(matrix.size(), false);

    pq.push({0, start});  // {cost, node}
    visited[start] = true;

    cout << "Best First Search order: ";
    while (!pq.empty()) {
        int node = pq.top().second;
        pq.pop();
        cout << node << " ";

        for (int i = 0; i < matrix.size(); i++) {
            if (matrix[node][i] != 0 && !visited[i]) {
                pq.push({matrix[node][i], i});
                visited[i] = true;
            }
        }
    }
    cout << endl;
}

void BeamSearch(const vector<vector<int>>& matrix, int start, int beam_width) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<bool> visited(matrix.size(), false);
    pq.push({0, start});
    visited[start] = true;

    cout << "Beam Search order: ";
    while (!pq.empty()) {
        vector<pair<int, int>> candidates;

        for (int i = 0; i < beam_width && !pq.empty(); i++) {
            candidates.push_back(pq.top());
            pq.pop();
        }

        for (auto& candidate : candidates) {
            int node = candidate.second;
            cout << node << " ";

            for (int i = 0; i < matrix.size(); i++) {
                if (matrix[node][i] != 0 && !visited[i]) {
                    pq.push({matrix[node][i], i});
                    visited[i] = true;  
                }
            }
        }

        if (pq.empty()) break;
    }
    cout << endl;
}

void A_star(vector<vector<int>> matrix, int start, int goal, vector<int> h) {
    int n = matrix.size();
    vector<int> g(n, INT_MAX);  // Cost from start to each node 
    vector<bool> visited(n, false);
    vector<int> parent(n, -1);  // To reconstruct the path

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    g[start] = 0;
    pq.push({h[start], start});  // Push the start node with its heuristic cost

    cout << "A* Search order: ";
    
    while (!pq.empty()) {
        int node = pq.top().second;
        pq.pop();

        if (visited[node]) continue;  
        visited[node] = true;
        
        cout << node << " ";
        
        if (node == goal) {
            cout << "\nGoal " << goal << " reached!" << endl;
            return;
        }

        for (int i = 0; i < n; i++) {
            if (matrix[node][i] != 0) {  // If there is a connection
                int tentative_g = g[node] + matrix[node][i];  //  tentative cost

                if (tentative_g < g[i]) { 
                    g[i] = tentative_g;
                    int f = g[i] + h[i];  // Total cost
                    pq.push({f, i});
                    parent[i] = node;  // Update parent
                }
            }
        }
    }

    cout << "\nGoal " << goal << " is unreachable." << endl;
}

int main()
{
    int num_nodes=10, start=0;
    vector<vector<int>> matrix = {
        {0, 6, 3, 1, 0, 0, 0, 0, 0, 0},
        {6, 0, 2, 6, 3, 4, 0, 0, 0, 0},
        {3, 2, 0, 0, 4, 5, 0, 0, 0, 0},
        {1, 6, 0, 0, 7, 8, 9, 0, 0, 0},
        {0, 3, 4, 7, 0, 6, 9, 9, 0, 0},
        {0, 4, 5, 8, 6, 0, 8, 9, 0, 0},
        {0, 0, 0, 9, 9, 8, 0, 11, 12, 14},
        {0, 0, 0, 0, 9, 9, 11, 0, 14, 15},
        {0, 0, 0, 0, 0, 0, 12, 14, 0, 0},
        {0, 0, 0, 0, 0, 0, 14, 15, 0, 0}};

    vector<int> heuristic = {15, 13, 13, 12, 10, 9, 7, 6, 5, 0};

    cout<<"\nDepth First Search without considering any cost: \n";
    DFS(matrix,start);

    cout<<"\n\nBreadth First Search without considering any cost:\n";
    BFS(matrix,start);

    cout<<"\n\nBest First Search considering only g value:\n";
    BestFirstSearch(matrix,start);

    cout<<"\n\nIterative Deepening by exploring best node first:\n";
    IDS(matrix,start);

    cout<<"\n\nBeam Search (Width=2) by giving preference to best node:";
    BeamSearch(matrix,start,2);

    cout<<"\n\nA* algorithm by considering both g and h' :\n";
    A_star(matrix, start, 9,heuristic);

    return 0;
}

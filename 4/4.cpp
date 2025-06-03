#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

void addEdge(vector<vector<int>> &adj, int u, int v) {
  adj[u].push_back(v);
  adj[v].push_back(u);
}

void BFS(vector<vector<int>> &adj, vector<bool> &visited, int start, int end) {
  int n = (int)adj.size();
  vector<int> parent(n, -1);
  visited[start] = true;

  queue<int> q;
  q.push(start);
  while (!q.empty()) {
    int node = q.front();
    q.pop();

    for (int neighbor : adj[node]) {
      if (!visited[neighbor]) {
        visited[neighbor] = true;
        parent[neighbor] = node;
        q.push(neighbor);
      }
    }
  }

  vector<int> path;
  for (int at = end; at != -1; at = parent[at]) path.push_back(at);

  if (path.back() != start) {
    cout << -1 << '\n';
    return;
  }

  reverse(path.begin(), path.end());
  cout << path.size() - 1 << '\n';
  for (const auto &p : path) cout << p << ' ';
  cout << '\n';
}

int main() {
  int n, m;
  cin >> n >> m;

  vector<vector<int>> adj(n + 1);
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    addEdge(adj, u, v);
  }

  int start, end;
  cin >> start >> end;
  vector<bool> visited(n + 1, false);
  BFS(adj, visited, start, end);
}

#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

typedef pair<int, int> pii;

const int MX = 1e9;

void addEdge(vector<vector<pii>>& graph, int u, int v, int w) {
  graph[u].push_back({v, w});
  graph[v].push_back({u, w});
}

void updateEdge(vector<vector<pii>>& graph, int u, int v, int w) {
  for (auto& e : graph[u]) {
    if (e.first == v) {
      e.second = w;
      break;
    }
  }

  for (auto& e : graph[v]) {
    if (e.first == u) {
      e.second = w;
      break;
    }
  }
}

void dijkstra(const vector<vector<pii>>& graph, int source, int end) {
  int n = (int)graph.size();
  vector<int> dist(n, MX);
  vector<int> parent(n, -1);
  dist[source] = 0.0;

  priority_queue<pii, vector<pii>, greater<pii>> pq;
  pq.push({0, source});
  while (!pq.empty()) {
    auto [w, u] = pq.top();
    pq.pop();

    if (w > dist[u]) continue;
    for (const auto& [v, weight] : graph[u]) {
      if (dist[u] + weight < dist[v]) {
        dist[v] = dist[u] + weight;
        parent[v] = u;
        pq.push({dist[v], v});
      }
    }
  }

  if (dist[end] == MX) cout << -1 << "\nKedua kota tidak terhubung\n";
  else {
    cout << dist[end] << " jam\n";
    vector<int> path;
    for (int v = end; v != -1; v = parent[v]) path.push_back(v);

    reverse(path.begin(), path.end());
    cout << "Rute: ";
    for (const auto& v : path) cout << v + 1 << ' ';
    cout << "\n";
  }
}

int main() {
  int n, m;
  cin >> n >> m;

  vector<vector<pii>> graph(n);
  for (int i = 0; i < m; ++i) {
    int u, v, t;
    cin >> u >> v >> t;
    addEdge(graph, u - 1, v - 1, t);
  }

  int source, end;
  cin >> source >> end;
  source--, end--;
  dijkstra(graph, source, end);

  int k;
  cin >> k;
  for (int i = 0; i < k; ++i) {
    int u, v, t;
    cin >> u >> v >> t;
    updateEdge(graph, u - 1, v - 1, t);
  }

  dijkstra(graph, end, source);
}

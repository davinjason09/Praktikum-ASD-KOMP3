#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

typedef pair<int, double> pid;
typedef pair<double, int> pdi;

const int MX = 1e9;

void addEdge(vector<vector<pid>>& graph, int u, int v, double w) {
  graph[u].push_back({v, w});
  graph[v].push_back({u, w});
}

void dijkstra(const vector<vector<pid>>& graph, int source, int end) {
  int n = (int)graph.size();
  vector<double> dist(n, MX);
  vector<int> parent(n, -1);
  dist[source] = 0.0;

  priority_queue<pdi, vector<pdi>, greater<pdi>> pq;
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
    cout << dist[end] << "jam\n";
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

  vector<vector<pid>> graph(n);
  for (int i = 0; i < m; i++) {
    int p, q, s, v;
    cin >> p >> q >> s >> v;
    double t = (double)s / v;
    addEdge(graph, p - 1, q - 1, t);
  }

  int source, end;
  cin >> source >> end;
  source--, end--;
  dijkstra(graph, source, end);
}

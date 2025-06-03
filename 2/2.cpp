#include <algorithm>
#include <iostream>
#include <numeric>
#include <utility>
#include <vector>
using namespace std;

typedef pair<int, int> pii;

struct DSU {
  vector<int> parent, rank;

  DSU(int n) : parent(n), rank(n, 0) {
    iota(parent.begin(), parent.end(), 0);
  }

  int find(int u) {
    return parent[u] == u ? u : parent[u] = find(parent[u]);
  }

  void unite(int u, int v) {
    u = find(u);
    v = find(v);
    if (u != v) {
      if (rank[u] < rank[v]) swap(u, v);
      parent[v] = u;
      if (rank[u] == rank[v]) rank[u]++;
    }
  }
};

int main() {
  int n, m;
  cin >> n >> m;

  vector<vector<int>> edges(m);
  int u, v, w;
  for (int i = 0; i < m; ++i) {
    cin >> u >> v >> w;
    edges[i] = {u, v, w};
  }

  DSU dsu(n);
  vector<pii> mst_edges;
  sort(edges.begin(), edges.end(), [](const vector<int> &a, const vector<int> &b) {
    return a[2] < b[2];
  });

  int totalWeight = 0;
  int edgeCount = 0;

  for (const auto &e : edges) {
    u = e[0];
    v = e[1];
    w = e[2];

    if (dsu.find(u) != dsu.find(v)) {
      dsu.unite(u, v);
      mst_edges.emplace_back(u, v);
      totalWeight += w;
      edgeCount++;

      if (edgeCount == n - 1) break;
    }
  }

  cout << totalWeight << '\n';
  for (const auto &[u, v] : mst_edges) cout << u << ' ' << v << '\n';
}

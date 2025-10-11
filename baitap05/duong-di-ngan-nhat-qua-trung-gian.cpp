#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;

typedef pair<int, int> ii; 
const int INF = 1000000;

int n, m, s, t, x;
vector<vector<ii>> adj;

pair<vector<int>, vector<int>> dijkstra(int start) {
    vector<int> dist(n + 1, INF), prev(n + 1, -1);
    priority_queue<ii, vector<ii>, greater<ii>> pq;
    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        auto [du, u] = pq.top(); pq.pop();
        if (du != dist[u]) continue;
        for (auto [w, v] : adj[u]) {
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                prev[v] = u;
                pq.push({dist[v], v});
            }
        }
    }
    return {dist, prev};
}

// Truy vết đường đi
vector<int> getPath(int s, int t, const vector<int>& prev) {
    vector<int> path;
    for (int v = t; v != -1; v = prev[v]) path.push_back(v);
    reverse(path.begin(), path.end());
    return path;
}

int main() {
    cin >> n >> m >> s >> t >> x;
    adj.assign(n + 1, {});
    for (int i = 0; i < m; i++) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].push_back({w, v});
    }

    auto [ds, ps] = dijkstra(s);
    auto [dx, px] = dijkstra(x);

    if (ds[x] == INF || dx[t] == INF) {
        cout << "Khong co duong di tu " << s << " den " << t << " qua " << x << endl;
        return 0;
    }

    vector<int> path1 = getPath(s, x, ps);
    vector<int> path2 = getPath(x, t, px);
    path2.erase(path2.begin());
    path1.insert(path1.end(), path2.begin(), path2.end());

    cout << path1.size() << " " << ds[x] + dx[t] << endl;
    for (int v : path1) cout << v << " ";
    cout << endl;
}

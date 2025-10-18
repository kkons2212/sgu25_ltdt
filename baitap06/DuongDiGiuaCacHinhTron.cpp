#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
#include <algorithm>
using namespace std;
#define FI "DuongDiGiuaCacHinhTron.INP"    
#define FO "DuongDiGiuaCacHinhTron.OUT"
struct Circle {
    double x, y, r;
};

struct State {
    int id;       // chỉ số hình tròn
    int jumps;    // số lần nhảy
    int steps;    // số hình tròn đã đi qua
    bool operator>(const State& other) const {
        if (jumps != other.jumps) return jumps > other.jumps;
        return steps > other.steps;
    }
};

// ----------- HÀM XÂY DỰNG ĐỒ THỊ -----------
vector<vector<pair<int, int>>> buildGraph(const vector<Circle> &c, int N) {
    vector<vector<pair<int, int>>> adj(N + 1);
    for (int i = 1; i <= N; i++) {
        for (int j = i + 1; j <= N; j++) {
            double d = hypot(c[i].x - c[j].x, c[i].y - c[j].y) - (c[i].r + c[j].r);
            if (d <= 50.0) {
                adj[i].push_back({j, 0});
                adj[j].push_back({i, 0});
            } else if (d <= 60.0) {
                adj[i].push_back({j, 1});
                adj[j].push_back({i, 1});
            }
        }
    }
    return adj;
}

// ----------- HÀM DIJKSTRA 2 TIÊU CHÍ -----------
void dijkstra(int S, const vector<vector<pair<int, int>>> &adj,
              vector<pair<int, int>> &dist, vector<int> &prev) {
    const int INF = 1e9;
    int N = adj.size() - 1;
    dist.assign(N + 1, {INF, INF});
    prev.assign(N + 1, -1);

    priority_queue<State, vector<State>, greater<State>> pq;
    dist[S] = {0, 0};
    pq.push({S, 0, 0});

    while (!pq.empty()) {
        State u = pq.top();
        pq.pop();

        if (make_pair(u.jumps, u.steps) > dist[u.id]) continue;

        for (auto [v, type] : adj[u.id]) {
            pair<int, int> newCost = {u.jumps + type, u.steps + 1};
            if (newCost < dist[v]) {
                dist[v] = newCost;
                prev[v] = u.id;
                pq.push({v, newCost.first, newCost.second});
            }
        }
    }
}

// ----------- HÀM TRUY VẾT VÀ IN KẾT QUẢ -----------
void tracePath(int S, int T, const vector<int> &prev,
               const vector<pair<int, int>> &dist, const vector<Circle> &c) {
    if (dist[T].first == 1e9) {
        cout << 0 << "\n";
        return;
    }

    vector<int> path;
    for (int v = T; v != -1; v = prev[v])
        path.push_back(v);
    reverse(path.begin(), path.end());

    cout << 1 << "\n";
    cout << dist[T].first << " " << path.size() << "\n";

    for (int i = 0; i < (int)path.size(); i++) {
        int type = 0;
        if (i > 0) {
            double d = hypot(c[path[i]].x - c[path[i - 1]].x,
                             c[path[i]].y - c[path[i - 1]].y)
                       - (c[path[i]].r + c[path[i - 1]].r);
            type = (d > 50.0 ? 1 : 0);
        }
        cout << path[i] << " " << type << "\n";
    }
}


int main() {
    freopen(FI, "r", stdin);
    freopen(FO, "w", stdout);

    int N, S, T;
    cin >> N >> S >> T;

    vector<Circle> c(N + 1);
    for (int i = 1; i <= N; i++)
        cin >> c[i].x >> c[i].y >> c[i].r;

    vector<vector<pair<int, int>>> adj = buildGraph(c, N);

    vector<pair<int, int>> dist;
    vector<int> prev;

    dijkstra(S, adj, dist, prev);
    tracePath(S, T, prev, dist, c);

    return 0;
}

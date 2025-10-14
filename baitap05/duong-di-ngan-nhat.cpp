#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const int INF = 100000;

// Hàm Dijkstra trả về đường đi và khoảng cách ngắn nhất
pair<vector<int>, int> dijkstra(int n, int m, int s, int t, const vector<vector<int>>& w) {
    vector<int> dist(n + 1, INF);
    vector<bool> tham(n + 1, false);
    vector<int> truoc(n + 1, -1);
    dist[s] = 0;

    for (int i = 1; i <= n; i++) {
        int u = -1, mindist = INF;
        for (int j = 1; j <= n; j++)
            if (!tham[j] && dist[j] < mindist)
                mindist = dist[j], u = j;

        if (u == -1) break;
        tham[u] = true;

        for (int v = 1; v <= n; v++)
            if (!tham[v] && w[u][v] != INF && dist[v] > dist[u] + w[u][v]) {
                dist[v] = dist[u] + w[u][v];
                truoc[v] = u;
            }
    }

    // Truy vết đường đi
    vector<int> duongdi;
    for (int v = t; v != -1; v = truoc[v])
        duongdi.push_back(v);
    reverse(duongdi.begin(), duongdi.end());

    return {duongdi, dist[t]};
}

int main() {
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    vector<vector<int>> w(n + 1, vector<int>(n + 1, INF));

    for (int i = 0; i < m; i++) {
        int u, v, trongso;
        cin >> u >> v >> trongso;
        w[u][v] = trongso;
    }

    auto [duongdi, kc] = dijkstra(n, m, s, t, w);

    cout << duongdi.size() << " " << kc << endl;
    for (int v : duongdi) cout << v << " ";
    cout << endl;

    return 0;
}

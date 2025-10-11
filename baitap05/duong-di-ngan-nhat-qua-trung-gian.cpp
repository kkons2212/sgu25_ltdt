#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int INF = 1e9;
int n, m, s, t, x;
vector<vector<pair<int, int>>> adj; 


pair<vector<int>, vector<int>> dijkstra_label(int start) {
    vector<int> dist(n + 1, INF);   
    vector<int> prev(n + 1, -1);   
    vector<bool> label(n + 1, false); 

    dist[start] = 0;


    for (int i = 1; i <= n; i++) {
        int u = -1;

        for (int v = 1; v <= n; v++) {
            if (!label[v] && (u == -1 || dist[v] < dist[u]))
                u = v;
        }

    
        if (u == -1 || dist[u] == INF) break;

        label[u] = true; 

      
        for (auto [w, v] : adj[u]) {
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                prev[v] = u;
            }
        }
    }

    return {dist, prev};
}

vector<int> getPath(int s, int t, const vector<int>& prev) {
    vector<int> path;
    for (int v = t; v != -1; v = prev[v])
        path.push_back(v);
    reverse(path.begin(), path.end());
    return path;
}

int main() {
    cin >> n >> m >> s >> t >> x;
    adj.assign(n + 1, {});

    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({w, v}); // đồ thị có hướng
    }

 
    auto [ds, ps] = dijkstra_label(s);
    auto [dx, px] = dijkstra_label(x);


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

    return 0;
}

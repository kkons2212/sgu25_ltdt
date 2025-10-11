#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

typedef pair<int, int> ii; // cặp (khoảng cách, đỉnh)
const int INF = 1e9;

pair<vector<int>, vector<int>> dijkstra(int s, int n, const vector<vector<ii>>& adj) {
    vector<int> dist(n + 1, INF);  
    vector<int> prev(n + 1, -1);   
    priority_queue<ii, vector<ii>, greater<ii>> pq; // hàng đợi ưu tiên (min-heap)

    dist[s] = 0;
    pq.push(ii(0, s)); // (khoảng cách, đỉnh)

    while (!pq.empty()) {
        ii p = pq.top();
        pq.pop();

        int du = p.first;  // khoảng cách hiện tại
        int u = p.second;  // đỉnh hiện tại

        if (du != dist[u]) continue; // nếu không còn tối ưu thì bỏ qua

        // duyệt các đỉnh kề của u
        for (int i = 0; i < adj[u].size(); i++) {
            int w = adj[u][i].first;   // trọng số cạnh
            int v = adj[u][i].second;  // đỉnh kề

            // nếu có đường ngắn hơn → cập nhật
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                prev[v] = u;
                pq.push(ii(dist[v], v)); // đẩy vào hàng đợi
            }
        }
    }

    return make_pair(dist, prev); // trả về cả hai mảng
}

vector<int> getPath(int s, int t, const vector<int>& prev) {
    vector<int> path;
    for (int v = t; v != -1; v = prev[v])
        path.push_back(v);
    reverse(path.begin(), path.end());
    return path;
}

int main() {
    int n, m, s, t;
    cin >> n >> m >> s >> t;

    vector<vector<ii>> adj(n + 1); // danh sách kề
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back(ii(w, v)); // đồ thị có hướng
    }

    // chạy Dijkstra từ s
    pair<vector<int>, vector<int>> result = dijkstra(s, n, adj);
    vector<int> dist = result.first;
    vector<int> prev = result.second;

    // kiểm tra có đường đi không
    if (dist[t] == INF) {
        cout << "Khong co duong di tu " << s << " den " << t << endl;
        return 0;
    }

    // truy vết đường đi
    vector<int> path = getPath(s, t, prev);

    // in kết quả
    cout << path.size() << " " << dist[t] << endl;
    for (int v : path) cout << v << " ";
    cout << endl;

    return 0;
}

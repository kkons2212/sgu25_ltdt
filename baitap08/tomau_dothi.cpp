#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int n, m;
vector<vector<int>> danhsachke;   // danh sách kề
vector<int> mau;          // màu của mỗi đỉnh
vector<bool> visited;     // đánh dấu đã thăm

// Hàm đọc dữ liệu
void doc() {
    cin >> n >> m;
    danhsachke.assign(n + 1, {});
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        danhsachke[u].push_back(v);
        danhsachke[v].push_back(u);
    }
}

// Hàm BFS để duyệt từng thành phần liên thông
void BFS(int start, vector<int>& thuTu) {
    queue<int> q;
    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        thuTu.push_back(u);

        for (int v : danhsachke[u]) {
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }
}

// Hàm xử lý tô màu
void xuly() {
    mau.assign(n + 1, 0);
    visited.assign(n + 1, false);
    vector<int> thuTu; // lưu thứ tự duyệt BFS

    for (int i = 1; i <= n; i++) {
        if (!visited[i]) BFS(i, thuTu);
    }

    // tô màu lần lượt
    for (int u : thuTu) {
        vector<bool> used(n + 1, false);
        for (int v : danhsachke[u]) {
            if (mau[v] != 0)
                used[mau[v]] = true;
        }

        int c = 1;
        while (used[c]) c++;
        mau[u] = c;
    }
}

// Hàm xuất kết quả
void xuat() {
    int k = 0;
    for (int i = 1; i <= n; i++) {
        if (mau[i] > k)
            k = mau[i];
    }

    cout << k << "\n";
    for (int color = 1; color <= k; color++) {
        for (int i = 1; i <= n; i++) {
            if (mau[i] == color)
                cout << i << " ";
        }
        cout << "\n";
    }
}

// Hàm main
int main() 
{
    freopen("tomau_dothi.inp","r",stdin);
    doc();
    xuly();
    xuat();
    return 0;
}

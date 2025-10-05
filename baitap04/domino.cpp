#include <iostream>
#include <vector>
#include <stack>

using namespace std;

// Lưu một domino (cạnh) dưới dạng hai nửa x và y
struct Domino { int x, y; };

// Một mục trong danh sách kề: đỉnh đích và id của cạnh
struct AdjEntry { int to; int edgeId; };

int main() {
    // Đọc số lượng quân domino
    int n;
    if (!(cin >> n)) return 0;


    vector<Domino> dom(n + 1);

    const int MAXV = 7; 
    vector<vector<AdjEntry>> adj(MAXV); // danh sách kề

    for (int i = 1; i <= n; ++i) {
        int a, b;
        cin >> a >> b;
        dom[i] = {a, b};
        // đẩy vào danh sách kề (vì đồ thị vô hướng nên thêm cả hai chiều)
        adj[a].push_back({b, i});
        adj[b].push_back({a, i});
    }

    // Tìm một đỉnh bắt đầu có bậc > 0 (nếu có)
    int startVertex = -1;
    vector<int> degree(MAXV, 0);
    for (int v = 0; v < MAXV; ++v) {
        degree[v] = (int)adj[v].size();
        if (degree[v] > 0 && startVertex == -1) startVertex = v;
    }

    // Nếu không có cạnh nào
    if (startVertex == -1) {
        // Nếu n == 0 thì coi là có vòng rỗng hợp lệ, ngược lại không thể tạo vòng
        if (n == 0) cout << 1 << "\n";
        else cout << 0 << "\n";
        return 0;
    }

    // Kiểm tra điều kiện cần cho chu trình Euler: mọi đỉnh có bậc chẵn
    for (int v = 0; v < MAXV; ++v) {
        if (degree[v] % 2 != 0) {
            cout << 0 << "\n";
            return 0;
        }
    }

    // Kiểm tra liên thông trên các đỉnh có bậc > 0 (DFS dùng stack)
    vector<int> visited(MAXV, 0);
    stack<int> dfsStack;
    dfsStack.push(startVertex);
    visited[startVertex] = 1;
    while (!dfsStack.empty()) {
        int u = dfsStack.top();
        dfsStack.pop();
        for (const AdjEntry &e : adj[u]) {
            if (!visited[e.to]) {
                visited[e.to] = 1;
                dfsStack.push(e.to);
            }
        }
    }
    for (int v = 0; v < MAXV; ++v) {
        if (degree[v] > 0 && !visited[v]) {
            // Có đỉnh có cạnh nhưng không cùng thành phần liên thông
            cout << 0 << "\n";
            return 0;
        }
    }

    // Nếu đạt điều kiện, dùng Hierholzer để xây chu trình Euler
    vector<int> iter(MAXV, 0);      // iterator cho danh sách kề mỗi đỉnh
    vector<char> usedEdge(n + 1, 0);// đánh dấu mỗi cạnh đã dùng chưa
    vector<int> circuit;            // lưu thứ tự đỉnh khi "backtrack"
    stack<int> pathStack;
    pathStack.push(startVertex);

    while (!pathStack.empty()) {
        int v = pathStack.top();

        // tìm cạnh chưa dùng từ v (bỏ qua các cạnh đã dùng)
        while (iter[v] < (int)adj[v].size() && usedEdge[adj[v][iter[v]].edgeId]) {
            ++iter[v];
        }

        if (iter[v] == (int)adj[v].size()) {
            // không còn cạnh chưa dùng -> đưa v vào circuit (lúc backtrack)
            circuit.push_back(v);
            pathStack.pop();
        } else {
            // đi theo cạnh chưa dùng
            AdjEntry e = adj[v][iter[v]];
            usedEdge[e.edgeId] = 1; // đánh dấu cạnh đã dùng
            pathStack.push(e.to);
        }
    }

    // Chu trình hợp lệ phải có đúng n+1 đỉnh (chu trình đóng)
    if ((int)circuit.size() != n + 1) {
        cout << 0 << "\n";
        return 0;
    }
    cout<<"\n";
    // circuit đang ở dạng "hoàn thành" (ngược) -> in từ cuối về đầu
    cout << 1 << "\n";
    for (int i = (int)circuit.size() - 1; i > 0; --i) {
        cout << circuit[i] << " " << circuit[i - 1] << "\n";
    }

    return 0;
}
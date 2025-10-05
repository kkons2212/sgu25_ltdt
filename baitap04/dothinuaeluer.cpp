#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

int n;
vector<vector<int>> matranke;
vector<vector<int>> danhsachke;
vector<int> bac;
vector<bool> tham;
vector<int> duongdi;

// DFS kiểm tra liên thông
void kiemtralienthong(int batdau) {
    stack<int> st;
    st.push(batdau);
    tham[batdau] = true;
    while (!st.empty()) {
        int u = st.top(); st.pop();
        for (int v : danhsachke[u]) {
            if (!tham[v]) {
                tham[v] = true;
                st.push(v);
            }
        }
    }
}

// Hierholzer dùng đệ quy
void euler(int u, vector<vector<int>>& adj) {
    for (int v = 0; v < n; v++) {
        if (adj[u][v]) {                // có cạnh
            adj[u][v] = adj[v][u] = 0;  // đánh dấu đã đi
            euler(v, adj);              // đi tiếp
        }
    }
    duongdi.push_back(u);
}

int main() {
    cin >> n;
    matranke.assign(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> matranke[i][j];

    danhsachke.assign(n, {});
    bac.assign(n, 0);
    tham.assign(n, false);

    // Xây danh sách kề + bậc
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matranke[i][j]) {
                danhsachke[i].push_back(j);
                bac[i]++;
            }
        }
    }

    // Tìm đỉnh bắt đầu
    int batdau = -1;
    for (int i = 0; i < n; i++)
        if (bac[i] > 0) { batdau = i; break; }
    if (batdau == -1) { cout << 0; return 0; }

    // Kiểm tra liên thông
    kiemtralienthong(batdau);
    for (int i = 0; i < n; i++)
        if (bac[i] > 0 && !tham[i]) { cout << 0; return 0; }

    // Kiểm tra số đỉnh bậc lẻ
    vector<int> odd;
    for (int i = 0; i < n; i++)
        if (bac[i] % 2 != 0) odd.push_back(i);
    if (odd.size() != 0 && odd.size() != 2) { cout << 0; return 0; }

    // Sao chép ma trận để đánh dấu cạnh đi qua
    vector<vector<int>> temp = matranke;

    // Bắt đầu Euler từ đỉnh bậc lẻ (nếu có) hoặc bất kỳ đỉnh có cạnh
    int start = odd.empty() ? batdau : odd[0];
    euler(start, temp);

    cout << 1 << "\n";
    reverse(duongdi.begin(), duongdi.end());
    for (int u : duongdi)
        cout << u + 1 << " ";
    cout << "\n";
}

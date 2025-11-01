#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int n, m;
vector<vector<pair<int,int>>> danhsachcanh;
vector<bool> tham; //danh dau dinh da nam trong cay 
vector<int> canh_nho_nhat; // la trong so nho nhat cua canh
vector<int> truoc;

void prim(int start) {
    tham.assign(n + 1, false);
    canh_nho_nhat.assign(n + 1, INT_MAX);
    truoc.assign(n + 1, -1);

    canh_nho_nhat[start] = 0;
    int tong_trong_so = 0;
    int tong_canh = 0;

    for (int i = 1; i <= n; i++) {
        int u = -1, minWeight = INT_MAX;

        // B1: tìm đỉnh chưa thuộc cây có cạnh nhỏ nhất
        for (int v = 1; v <= n; v++) {
            if (!tham[v] && canh_nho_nhat[v] < minWeight) {
                minWeight = canh_nho_nhat[v];
                u = v;
            }
        }

        if (u == -1) break; // không còn đỉnh hợp lệ

        // B2: chọn u vào cây
        tham[u] = true;
        tong_trong_so += minWeight;
        if (truoc[u] != -1) tong_canh++;

        // B3: cập nhật các đỉnh kề
        for (auto [v, w] : danhsachcanh[u]) {
            if (!tham[v] && w < canh_nho_nhat[v]) {
                canh_nho_nhat[v] = w;
                truoc[v] = u;
            }
        }
    }

  
    cout << tong_canh << " " << tong_trong_so << "\n";
    for (int v = 1; v <= n; v++) {
        if (truoc[v] != -1)
            cout << truoc[v] << " " << v << " " << canh_nho_nhat[v] << "\n";
    }
}

int main() {
    freopen("Prim.inp", "r", stdin);
    cin >> n >> m;

    danhsachcanh.assign(n + 1, {});
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        danhsachcanh[u].push_back({v, w});
        danhsachcanh[v].push_back({u, w});
    }

    prim(1); // bắt đầu từ đỉnh 1
    return 0;
}
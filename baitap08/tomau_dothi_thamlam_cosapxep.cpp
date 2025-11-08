#include <iostream>
#include <vector>
#include <queue>
using namespace std;


int n, m;                      // số đỉnh, số cạnh
vector<vector<int>> ke;        // danh sách kề
vector<int> mau;               // màu cho từng đỉnh


void doc() 
{
    cin >> n >> m;
    ke.assign(n + 1, {});
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        ke[u].push_back(v);
        ke[v].push_back(u);
    }
}

// ======= HÀM XUẤT KẾT QUẢ =======
void xuat() {
    int soMau = 0;
    for (int i = 1; i <= n; i++)
        if (mau[i] > soMau) soMau = mau[i];

    cout<< soMau << "\n";
    for (int c = 1; c <= soMau; c++) 
    {
        for (int i = 1; i <= n; i++)
            if (mau[i] == c)
                cout << i << " ";
        cout << "\n";
    }
}

// ======= THUẬT TOÁN THAM LAM + SẮP XẾP =======

// Hàm sắp xếp giảm dần theo bậc 
void sapXepGiamDan(vector<pair<int,int>>& bac) {
    int n = bac.size();
    for (int i = 0; i < n - 1; i++) {
        int maxPos = i;
        for (int j = i + 1; j < n; j++)
            if (bac[j].first > bac[maxPos].first)
                maxPos = j;
        swap(bac[i], bac[maxPos]);
    }
}

// Thuật toán tham lam kết hợp sắp xếp 
void toMauThamLamSapXep() {
    mau.assign(n + 1, 0);
    vector<bool> visited(n + 1, false);

    // Tính bậc của từng đỉnh
    vector<pair<int,int>> bac;
    for (int i = 1; i <= n; i++)
        bac.push_back({(int)ke[i].size(), i});

    // Sắp xếp giảm dần theo bậc
    sapXepGiamDan(bac);

    // Duyệt BFS theo thứ tự đã sắp xếp
    for (auto &p : bac) {
        int start = p.second;
        if (visited[start]) 
        continue;

        queue<int> q;
        q.push(start);
        visited[start] = true;

        while (!q.empty()) {
            int u = q.front(); q.pop();

            // Tô màu đỉnh u
            vector<bool> used(n + 1, false);
            for (int v : ke[u])
                if (mau[v] != 0) used[mau[v]] = true;

            int c = 1;
            while (used[c]) c++;
            mau[u] = c;

            // Thêm đỉnh kề vào BFS
            for (int v : ke[u])
                if (!visited[v]) {
                    visited[v] = true;
                    q.push(v);
                }
        }
    }
   
}

// ======= MAIN =======
int main() {
   
    freopen("tomau_dothi_thamlam_cosapxep.inp","r",stdin);
    doc();
    toMauThamLamSapXep();
    xuat();
    return 0;
}

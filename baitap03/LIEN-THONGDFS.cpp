#include<iostream>
#include<vector>
#include<cstring>
using namespace std;
#define FI "LIEN-THONGDFS.INP"
#define FO "LIEN-THONGDFS.OUT"

vector<int> danhsach[10000];
vector<bool> tham;
vector<int> ketqua; // lưu các đỉnh đã duyệt
int n, s; // n: số đỉnh, s: đỉnh bắt đầu

void dfs(int u)
{
    tham[u] = true;
   if(u!=s) ketqua.push_back(u); // lưu lại đỉnh đã thăm
    for (int v : danhsach[u])
    {
        if (!tham[v])
        {
            dfs(v);
        }
    }
}

void nhap()
{
    cin >> n >> s;
    for (int i = 1; i <= n; i++)   // từ 1 đến n
    {
        int x;
        while (cin >> x)
        {
            if (x == -1) break;   // kết thúc danh sách kề của 1 đỉnh
            if (x == i) continue; // bỏ trường hợp tự kề
            danhsach[i].push_back(x);
        }
    }
    tham.assign(n + 1, false);
}

void xuat()
{
    dfs(s);
    cout << ketqua.size() << "\n";   // dòng 1: số lượng đỉnh
    for (int u : ketqua) cout << u << " ";  // dòng 2: danh sách đỉnh
}

int main()
{
    freopen(FI, "r", stdin);
    freopen(FO, "w", stdout);
    nhap();
    xuat();
}

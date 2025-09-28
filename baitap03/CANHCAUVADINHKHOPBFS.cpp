#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

#define FI "CANHCAUVADINHKHOPBFS.INP"
#define FO "CANHCAUVADINHKHOPBFS.OUT"

vector<vector<int>> danhsach;
vector<bool> tham;
int n, x, y, z;

void bfs(int s, int skip_u=-1, int skip_v=-1, int skip_node=-1)
{
    queue<int> q;
    tham[s] = true;
    q.push(s);

    while (!q.empty())
    {
        int u = q.front(); q.pop();
        for (int v : danhsach[u])
        {
            // Bỏ cạnh (x,y)
            if ((u == skip_u && v == skip_v) || (u == skip_v && v == skip_u)) continue;
            // Bỏ đỉnh z
            if (v == skip_node) continue;
            if (!tham[v])
            {
                tham[v] = true;
                q.push(v);
            }
        }
    }
}

int demTPLT(int skip_u=-1, int skip_v=-1, int skip_node=-1)
{
    tham.assign(n+1,false);
    int dem = 0;
    for (int i=1;i<=n;i++)
    {
        if (i == skip_node) continue; // bỏ luôn đỉnh
        if (!tham[i])
        {
            bfs(i, skip_u, skip_v, skip_node);
            dem++;
        }
    }
    return dem;
}

int main()
{
    freopen(FI,"r",stdin);
    freopen(FO,"w",stdout);

    cin >> n >> x >> y >> z;
    danhsach.resize(n+1);

    for (int i=1;i<=n;i++)
    {
        int v;
        while (cin >> v && v != -1)
        {
            danhsach[i].push_back(v);
            danhsach[v].push_back(i);
        }
    }

    // Đếm thành phần liên thông gốc
    int goc = demTPLT();

    // Kiểm tra cạnh cầu
    int sauCanh = demTPLT(x,y,-1);
    if (sauCanh > goc) cout << "canh cau\n";
    else cout << "khong la canh cau\n";

    // Kiểm tra đỉnh khớp
    int sauDinh = demTPLT(-1,-1,z);
    if (sauDinh > goc) cout << "dinh khop\n";
    else cout << "khong la dinh khop\n";

    return 0;
}

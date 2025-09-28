#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
#define FI "THANHPHANLIENTHONGFBFS.INP"
#define FO "THANHPHANLIENTHONGBFS.OUT"

vector<vector<int>> danhsach;
vector<bool> tham;
int n;

vector<int> bfs(int s)
{
    vector<int> comp;
    queue<int> q;
    q.push(s);
    tham[s] = true;

    while (!q.empty())
    {
        int u = q.front(); q.pop();
        comp.push_back(u);
        for (int v : danhsach[u])
        {
            if (!tham[v])
            {
                tham[v] = true;
                q.push(v);
            }
        }
    }
    return comp;
}

int main()
{
    freopen(FI, "r", stdin);
    freopen(FO, "w", stdout);

    cin >> n;
    danhsach.resize(n+1);
    tham.assign(n+1, false);

    for (int i = 1; i <= n; i++)
    {
        int v;
        while (cin >> v && v != -1)
        {
            danhsach[i].push_back(v);
            danhsach[v].push_back(i);
        }
    }

    vector<vector<int>> thanhphan;
    for (int i = 1; i <= n; i++)
    {
        if (!tham[i])
        {
            vector<int> comp = bfs(i);
            sort(comp.begin(), comp.end()); // in theo thứ tự tăng dần
            thanhphan.push_back(comp);
        }
    }

    cout << thanhphan.size() << "\n";
    for (auto &comp : thanhphan)
    {
        for (int u : comp) cout << u << " ";
        cout << "\n";
    }

    return 0;
}

#include<iostream>
#include<vector>
#include<queue>
using namespace std;
#define FI "LIENTHONGBFS.INP"
#define FO "LIENTHONGBFS.OUT"
vector<vector<int>> danhsach;
vector<bool> visited;
vector<int> ketqua; // lưu đỉnh duyệt được trừ đỉnh bắt đầu

void bfs(int start) {
    queue<int> q;
    visited[start] = true;
    q.push(start);
    while (!q.empty()) {
        int u = q.front(); 
        q.pop();
        if(u!=start)
        { 
            ketqua.push_back(u);
        }
        for (int v : danhsach[u]) {
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }
}

int main() {
    freopen(FI, "r", stdin);
    freopen(FO, "w", stdout);

    int n, x;
    cin >> n >> x;
   danhsach.resize(n+1,{});
   visited.resize(n+1, false);
    for (int i = 1; i <= n; i++) {
        int v;
        while (cin>>v && v!=-1) {
           
            danhsach[i].push_back(v);
        }
    }
    
    bfs(x);
    cout<<ketqua.size()<<endl;
    for(int u: ketqua)
    cout<<u<<" ";

    return 0;
}
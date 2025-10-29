#include<iostream>
#include<vector>
#include<queue>
#include<set>
using namespace std;

int n,m;
vector<set<int>> danhsachke;
vector<bool> visited;
vector<pair<int,int>> caykhung_bfs;
void doc()
{
    int n,m;
    danhsachke.resize(n+1);
    for(int i=1;i<=m;i++)
    {
        int u,v;
        cin>>u>>v;
        danhsachke[u].insert(v);
        danhsachke[v].insert(u);
    }
}
void duyetbfs(int u)
{
   queue<int> q;
   visited[u]=true;
   q.push(u);
}
int main()
{

}
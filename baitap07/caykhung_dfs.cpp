#include<iostream>
#include<vector>
#include<set>
using namespace std;


int n,m;

vector<set<int>> danhsachke;
vector<bool>visited;
vector<pair<int,int>> caykhung_dfs;

void doc()
{
    cin>>n>>m;
    danhsachke.resize(n+1);
    for(int i=1;i<=m;i++)
    {
        int u,v;
        cin>>u>>v;
        danhsachke[u].insert(v);
        danhsachke[v].insert(u);
    }
}
void duyet_dfs(int u)
{

    visited[u]=true;
    for( auto &v: danhsachke[u])
    {
        if(visited[v]==false)
        {
            visited[v]=true;
            caykhung_dfs.push_back({u,v});
            duyet_dfs(v);
        }
    }
}
void in()
{
    cout<<caykhung_dfs.size()<<"\n";
    for(int i=0;i< caykhung_dfs.size();i++)
    {
        cout<<caykhung_dfs[i].first<<" "<<caykhung_dfs[i].second<<endl;
    }

}
int main()
{  
    freopen("caykhung_dfs.inp","r",stdin);
   doc();
   visited.resize(n+1,false);
   duyet_dfs(1);
   in();
   return 0;

}
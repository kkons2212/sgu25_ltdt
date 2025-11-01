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
void duyetbfs(int s)
{
   queue<int> q;
   visited[s]=true;
   q.push(s);
   while(!q.empty())
{
      int u= q.front();
      q.pop();
      for(auto &v: danhsachke[u])
      {
         if(visited[v]==false)
         {
            visited[v]=true;
            caykhung_bfs.push_back({u,v});
            q.push(v);
         }
      }
}


}
void in()
{
    cout<<caykhung_bfs.size()<<"\n";
    for(int i=0;i< caykhung_bfs.size();i++)
    {
        cout<<caykhung_bfs[i].first<<" "<<caykhung_bfs[i].second<<endl;
    }

}
int main()
{
   
    freopen("caykhung_bfs.inp","r",stdin);
   doc();
   visited.resize(n+1,false);
   duyetbfs(1);
   in();
   return 0;
}
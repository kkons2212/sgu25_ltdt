#include<iostream>
#include<vector>
#include<algorithm>
#include<utility>
using namespace std;

struct edge
{
    int u,v;
    int w;
    edge(int _u=0,int _v=0,int _w=0)
    {
         u = _u;
         v = _v;
         w = _w;
    }
};
int n,m;
vector<edge> danhsachcanh;
vector<vector<pair<int,int>>> caykhung_nhonhat;
vector<int> tham;
void sapxep()
{
    for(int i=0;i<m-1;i++)
    {
        for(int j=i+1;j<m;j++)
        {
            if(danhsachcanh[i].w>danhsachcanh[j].w)
            swap(danhsachcanh[i],danhsachcanh[j]);
        }
    }
}

bool check_dfs(int u, int v) //kiem tra xem co duong di tu u den v hay khong
{
    tham[u]=1;
    if(u==v)
    return true;
    for(auto [nextv,w]:caykhung_nhonhat[u]) //kiem tra nhung dinh ke voi u
    {
        if(!tham[nextv])
        if(check_dfs(nextv,v)==true)
        {
            return true;
        }
    }
    return false;
}
int main()
{
    freopen("Kruskal.inp","r",stdin);
    cin>>n>>m;
    danhsachcanh.resize(m);
    for(int i=0;i<m;i++)
    {
        int u,v,w;
        cin>>u>>v>>w;
        danhsachcanh[i] = edge(u,v,w);
    }
    sapxep();
    caykhung_nhonhat.resize(n+1,{});
    int tong_trong_so =0;
    int tong_canh=0;
    for(auto &e: danhsachcanh)
    {
        tham.assign(n+1,0);
        if(check_dfs(e.u,e.v)==false)
        {
          caykhung_nhonhat[e.u].push_back({e.v,e.w});
          caykhung_nhonhat[e.v].push_back({e.u,e.w});
          tong_trong_so=tong_trong_so+e.w;
          tong_canh++;
          if(tong_canh == n-1)
          break;
        }
    }
    cout<<tong_canh<<" "<<tong_trong_so<<endl;
    for(int u=1;u<=n;u++)
    {
        for(auto[v,w]:caykhung_nhonhat[u])
        {
            if(u<v)
            {
                cout<<u<<" "<<v<<" "<<w<<"\n";
            }
        }
    }
    return 0;
}
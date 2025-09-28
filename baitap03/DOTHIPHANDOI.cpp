#include<iostream>
#include<vector>
using namespace std;
#define FI "DOTHIPHANDOI.INP"
#define FO "DOTHIPHANDOI.OUT"
vector<vector<int>> danhsach;
vector<int> color;
bool flag=true;
int n;
void dfs(int u,int c)
{
    color[u]=c;
    for(int v: danhsach[u])
    {
        if(color[v]==-1)
        {
            dfs(v,1-c);
        }
        else 
        {
            if(color[v]==color[u])
            flag=false;
        }
    }
}
int main()
{
    freopen(FI,"r",stdin);
    freopen(FO,"w",stdout);
    cin>>n;
    danhsach.resize(n+1,{});
    color.resize(n+1,-1);
    for(int i=1;i<=n;i++)
    {
        int v;
        while(cin>>v && v!=-1)
        danhsach[i].push_back(v);
    }
   for(int i=1;i<=n;i++)
   {
    if(color[i]==-1)
    {
        dfs(i,0);
    }
   }
   if(flag)
   cout<<"DO THI PHAN DOI";
   else
   cout<<"DO THI KHONG PHAN DOI";
   return 0;
}

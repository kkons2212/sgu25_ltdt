#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
#define FI "TIMDUONGDIBFS.INP"
#define FO "TIMDUONGDIBFS.OUT"
vector<vector<int>> danhsach;
vector<bool> tham;
vector<int> cha;
int n,x,y;
void bfs(int x,int muctieu)
{
   queue<int> q;
   q.push(x);
   tham[x]=true;
   while(!q.empty())
   {
    int u=q.front();
    q.pop();
    if(u==muctieu)
    break;
    for(int v:danhsach[u])
    {
        if(!tham[v])
        {
          tham[v]=true;
          cha[v]=u;
          q.push(v);
        }
    }
    }
}
int main()
{
    freopen(FI,"r",stdin);
    freopen(FO,"w",stdout);
    cin>>n>>x>>y;
    danhsach.resize(n+1,{});
    tham.resize(n+1,false);
    cha.resize(n+1,-1);
    for(int i=1;i<=n;i++)
    {
        int v;
        while(cin>>v&&v!=-1)
        {
        danhsach[i].push_back(v);
        danhsach[v].push_back(i);
        }
    }
   bfs(x,y);
   vector<int> duongdi;
   if(tham[y])
   {
    for(int tam=y;tam!=-1;tam=cha[tam])
    {
        duongdi.push_back(tam);
        if(tam==x) 
        break;
    }
    reverse(duongdi.begin(),duongdi.end());
   }
  cout<<duongdi.size()<<endl;
  for(int u:duongdi)
  cout<<u<<" ";
  return 0;
}
#include<iostream>
#include<vector>
#include<stack>
using namespace std;
#define FI "DFSKHONGDEQUY.INP"
#define FO "DFSKHONGDEQUY.OUT"
int n,x;
vector<vector<int>> danhsach;
vector<bool> tham;
vector<int> cha;
void dfs(int x)
{
    stack<int> st;
    st.push(x);
    tham[x]=true;
    while(!st.empty())
    { int u=st.top();
        st.pop();
        cout<<u<<" ";
    for(int v:danhsach[u])
    {
          if(tham[v]==false)
          {
            tham[v]=true;
            st.push(v);
          }
          
    }
}
}
int main ()
{
    freopen(FI,"r",stdin);
    freopen(FO,"w",stdout);
    cin>>n>>x;
    danhsach.resize(n+1,{});
    tham.resize(n+1,false);
        for(int i=1;i<=n;i++)
    {
        int v;
        while(cin>>v&&v!=-1)
        {
            danhsach[i].push_back(v);
        }
    }
    dfs(x);
    return 0;
}
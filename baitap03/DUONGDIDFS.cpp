#include<iostream>
#include<vector>
#include<stack>
#include<algorithm>
using namespace std;
#define FI "DUONGDIDFS.INP"
#define FO "DUONGDIDFS.OUT"
int n,x,y;
vector<vector<int>> danhsach;
vector<int> cha; //;uu cha cua dinh
vector<bool> tham;
void dfs(int batdau,int muctieu)
{
    stack<int> st;
    st.push(batdau);
    tham[batdau]=true;
    while(!st.empty())
    {
       int u= st.top();
       st.pop();
       if(u==muctieu) return;
       for(int v: danhsach[u])
       {
        if(tham[v]==false)
        {
           tham[v]=true;
           cha[v]=u;
           st.push(v);
        }
       }
    }

}
int main()
{   freopen(FI,"r",stdin);
    freopen(FO,"w",stdout);

    cin>>n>>x>>y;

    danhsach.resize(n+1,{});
    cha.resize(n+1,-1);
    tham.resize(n+1,false);
    
    for(int i=1;i<=n;i++)
    {
        int v;
        while(cin>>v&& v!=-1)
        {
            danhsach[i].push_back(v);
        }
    }
    dfs(x,y);
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
    for(int u: duongdi)
    cout<<u<<" ";
    cout<<"\n";
    return 0;
}

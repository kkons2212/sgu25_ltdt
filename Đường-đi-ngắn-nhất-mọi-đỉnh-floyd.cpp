#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int n,m;
const int INF=100000;
int main()
{
    cin>>n>>m;
    vector<vector<int>> khoangcach(n+1,vector<int>(n+1,INF));
    for(int i=0;i<=n;i++)
    {
        khoangcach[i][i]=0;
    }
    for(int i=0;i<m;i++)
    {
        int u,v,w;
        cin>>u>>v>>w;
        khoangcach[u][v]=khoangcach[v][u]=min(khoangcach[u][v],w);
    }
    for(int k=1;k<=n;k++)
    {
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=n;j++)
            {
                if(khoangcach[i][k]!=INF&&khoangcach[k][j]!=INF)
                {
                    khoangcach[i][j]=min(khoangcach[i][j],khoangcach[i][k]+khoangcach[k][j]);
                }
            }
        }
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        
            cout<< (khoangcach[i][j]==INF?0:khoangcach[i][j])<<" ";
            cout<<endl;
        
    }
    return 0;
}
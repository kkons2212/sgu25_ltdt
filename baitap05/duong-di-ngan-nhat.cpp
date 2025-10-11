#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
const int INF=100000;
int main()
{   
    int n,m,s,t; //dinh, canh bat dau ,ket thuc
    cin>>n>>m>>s>>t;
    vector<vector<int>> w(n+1,vector<int>(n+1,INF));//danh sach 
    for(int i=0;i<m;i++)
    {
        int u,v,trongso;
        cin>>u>>v>>trongso;
        w[u][v]=trongso;

    }
    vector<int> dist(n+1,INF);// khoang cach ngan nhat tu s
    vector<bool> tham(n+1,false);
    vector<int> truoc(n+1,-1);// luu dinh truoc do
    dist[s]=0;
    for(int i=1;i<=n;i++)
    {
        int u=-1,mindist=INF;
        for(int j=1;j<=n;j++)
        {
            if(!tham[j]&& dist[j]<mindist)
            {
                mindist=dist[j];
                u=j;

            }
        }
        if(u==-1)
        break;
        tham[u]=true;
        for(int v=1;v<=n;v++)
        {
            if(!tham[v]&&w[u][v]!=INF&& dist[v]> dist[u]+w[u][v])
            {
                dist[v]=dist[u]+w[u][v];
                truoc[v]=u;
            }
        }
        
    }
   if (dist[t] == INF) {
    cout << "Khong co duong di tu " << s << " den " << t << endl;
            } 
            else {
                cout << "Do dai duong di ngan nhat tu " << s << " den " << t << ": " << dist[t] << endl;
            }
            vector<int> duongdi;
            for (int v = t; v != -1; v = truoc[v]) 
            duongdi.push_back(v);

            cout << "Duong di: ";
            for (int i = duongdi.size() - 1; i >= 0; i--)
                cout << duongdi[i] << " ";
                cout << endl;
             cout <<"cac dinh da di qua:"<<duongdi.size();
   return 0;
}
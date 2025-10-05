#include<iostream>
#include<stack>
#include<vector>
using namespace std;

int n;
vector<vector<int>> a;
vector<int> duongdi;
vector<int> bac;
vector<vector<int>> danhsachke;

// kiểm tra liên thông bằng DFS stack
bool kiemtralienthong()
{   
    vector<bool> tham(n,false);
    int batdau=-1;

    for(int i=0;i<n;i++) {
        if(bac[i]>0) { batdau=i; break; }
    }
    if(batdau==-1) return true; // đồ thị không có cạnh

    stack<int> st;
    st.push(batdau);
    tham[batdau]=true;

    while(!st.empty()) {
        int u=st.top(); st.pop();
        for(int v: danhsachke[u]) {
            if(!tham[v]) {
                tham[v]=true;
                st.push(v);
            }
        }
    }
    for(int i=0;i<n;i++) {
        if(bac[i]>0 && !tham[i]) return false;
    }
    return true;
}

// tìm Euler path/cycle
void kiemtraeuler(int batdau)
{
    vector<vector<int>> temp = danhsachke; 
    vector<int> vitri(n, 0);
    stack<int> st;
    st.push(batdau);

    while (!st.empty()) {
        int u = st.top();
        while (vitri[u] < (int)temp[u].size() && temp[u][vitri[u]] == -1) 
        vitri[u]++;
        if (vitri[u] == (int)temp[u].size()) {
            duongdi.push_back(u);
            st.pop();
        } else {
            int v = temp[u][vitri[u]];
            temp[u][vitri[u]] = -1;
            // xóa cạnh ngược
            for (int &x : temp[v]) {
                if (x == u) { x = -1; break; }
            }
            st.push(v);
        }
    }
}

int main()
{   
    cin>>n;
    a.resize(n,vector<int>(n,0));
    for(int i=0;i<n;i++) {
        for(int j=0;j<n;j++) {
            cin>>a[i][j]; // ma trận kề
        }
    }

    danhsachke.resize(n);
    bac.resize(n,0);
    for(int i=0;i<n;i++) {
        for(int j=0;j<n;j++) {
            if(a[i][j]==1) {
                danhsachke[i].push_back(j);
                bac[i]++;
            }
        }
    }

    if(!kiemtralienthong()) {
        cout<<0;
        return 0;
    }

    vector<int> sodinhle;
    for(int i=0;i<n;i++) {
        if(bac[i]%2!=0)
            sodinhle.push_back(i);
    }

    if(!(sodinhle.size()==0 || sodinhle.size()==2)) {
        cout<<0;
        return 0;
    }

    cout<<1<<"\n";

    int batdau=0;
    if(sodinhle.size()==2) {
        batdau=sodinhle[0];
    } else {
        for(int i=0;i<n;i++) {
            if(bac[i]>0) {
                batdau=i;
                break;
            }
        }
    }

    kiemtraeuler(batdau);

    for(int i=0;i<(int)duongdi.size();i++) {
        cout<<duongdi[i]+1;
        if(i+1<(int)duongdi.size()) cout<<" ";
    }
}

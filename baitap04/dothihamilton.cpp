#include <iostream>
#include <vector>
using namespace std;

int n;
vector<vector<int>> a;
vector<int> path;
vector<bool> visited;
bool found = false;

void Try(int pos) {
    if (found) return;
    if (pos == n) {
        if (a[path[n - 1]][path[0]] == 1) {
            found = true;
            cout << 1 << "\n";
            for (int v : path) cout << v + 1 << " ";
            cout << path[0] + 1 << "\n";
        }
        return;
    }

    for (int v = 0; v < n; v++) {
        if (!visited[v] && a[path[pos - 1]][v] == 1) {
            visited[v] = true;
            path[pos] = v;
            Try(pos + 1);
            visited[v] = false;
        }
    }
}

int main() {
    cin >> n;
    a.assign(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> a[i][j];

    path.assign(n, -1);
    visited.assign(n, false);
    path[0] = 0;
    visited[0] = true;

    Try(1);
    if (!found) cout << 0;
}

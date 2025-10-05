void euler_matrix(int start, vector<vector<int>> adj) {
    stack<int> st;
    st.push(start);
    vector<int> path;

    while (!st.empty()) {
        int u = st.top();
        bool hasEdge = false;

        for (int v = 0; v < n; v++) {
            if (adj[u][v]) { // có cạnh
                adj[u][v] = adj[v][u] = 0; // xóa cạnh
                st.push(v);
                hasEdge = true;
                break;
            }
        }

        if (!hasEdge) {
            path.push_back(u);
            st.pop();
        }
    }

    cout << 1 << "\n";
    reverse(path.begin(), path.end());
    for (int u : path) cout << u + 1 << " ";
    cout << "\n";
}

void euler_list(int start, vector<vector<int>> adjList) {
    stack<int> st;
    st.push(start);
    vector<int> path;

    while (!st.empty()) {
        int u = st.top();
        if (!adjList[u].empty()) {
            int v = adjList[u].back();
            adjList[u].pop_back();

            // Xóa cạnh ngược (v -> u)
            auto it = find(adjList[v].begin(), adjList[v].end(), u);
            if (it != adjList[v].end())
                adjList[v].erase(it);

            st.push(v);
        } else {
            path.push_back(u);
            st.pop();
        }
    }

    cout << 1 << "\n";
    reverse(path.begin(), path.end());
    for (int u : path) cout << u + 1 << " ";
    cout << "\n";
}

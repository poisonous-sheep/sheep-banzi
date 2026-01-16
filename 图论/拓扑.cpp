vector<int> toposort() {
    vector<int> res;
    queue<int> q;
    rep(1, n) {
        if (d[i] == 0) q.push(i);
    }
    while (q.size()) {
        int u = q.front();
        q.pop();
        res.push_back(u);
        for (auto v : edge[u]) {
            d[v]--;
            if (d[v] == 0) q.push(v);
        }
    }
    return res;
}

void solve() {
    int n, m, s;
    cin >> n >> m >> s;

    // 建图
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        egde[u].push_back(v);
        egde[v].push_back(u);
    }

    // DFS 预处理
    auto dfs = [&](auto&& dfs, int u, int fa) -> void {
        dist[u] = dist[fa] + 1;
        pre[u][0] = fa;

        for (auto v : egde[u]) {
            if (v == fa) continue;
            dfs(dfs, v, u);
        }
    };

    dfs(dfs, s, 0);

    // 倍增表
    for (int i = 1; i <= 20; i++) {
        for (int j = 1; j <= n; j++) {
            pre[j][i] = pre[pre[j][i - 1]][i - 1];
        }
    }

    auto lca = [&](int x, int y) {
        if (dist[x] < dist[y]) swap(x, y);

        // 让 x 跳到和 y 同一深度
        for (int i = 20; i >= 0; i--) {
            if (dist[pre[x][i]] >= dist[y]) {
                x = pre[x][i];
            }
        }

        if (x == y) return x;

        // 一起往上跳
        for (int i = 20; i >= 0; i--) {
            if (pre[x][i] != pre[y][i]) {
                x = pre[x][i];
                y = pre[y][i];
            }
        }

        return pre[x][0];
    };

    while (m--) {
        int u, v;
        cin >> u >> v;
        cout << lca(u, v) << '\n';
    }
}

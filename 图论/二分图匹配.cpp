signed main() {
    int n1, n2, m;
    cin >> n1 >> n2 >> m;

    vector<vector<int>> adj(n1 + 1);

    for (int i = 1; i <= m; ++i) {
        int x, y;
        cin >> x >> y;

        // 二分图匹配只需要存左部点 -> 右部点
        adj[x].push_back(y);
    }

    // match[v] 表示右部点 v 当前匹配的左部点
    vector<int> match(n2 + 1);

    int ans = 0;

    // 枚举每一个左部点，尝试给它寻找匹配
    for (int i = 1; i <= n1; ++i) {

        // vis[v] 表示右部点 v
        // 在这一轮寻找增广路时是否已经访问过
        vector<int> vis(n2 + 1);

        auto dfs = [&](auto&& dfs, int x) -> bool {
            // 枚举左部点 x 能连接的所有右部点
            for (auto v : adj[x]) {

                // 如果这一轮已经访问过 v，就不能重复访问
                if (vis[v]) continue;

                // 标记 v 已经访问
                vis[v] = 1;

                // 如果 v 还没有匹配
                // 或者原来匹配 v 的左部点可以找到新的位置
                if (!match[v] || dfs(dfs, match[v])) {

                    // 让当前左部点 x 匹配右部点 v
                    match[v] = x;

                    // 成功找到一条增广路
                    return true;
                }
            }

            // 当前左部点无法找到匹配
            return false;
        };

        // 如果成功找到一条增广路
        // 最大匹配数量增加 1
        if (dfs(dfs, i)) {
            ans++;
        }
    }

    cout << ans << endl;
}

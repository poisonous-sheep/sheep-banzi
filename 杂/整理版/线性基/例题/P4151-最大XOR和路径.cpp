// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// P4151 最大XOR和路径
// 原题：https://www.luogu.com.cn/problem/P4151
// 所属知识点：线性基；使用模板：LinearBasis
// 题意：无向连通图求1到n的最大异或权路径，可重复边点。
// 转化：任意路径异或为一条树路径值加环空间组合；每条非树边产生环异或。
// 调用：DFS计算dis并insert(dis[u]^dis[v]^w)，最后qur(dis[n])。
// 复杂度：O((n+m)B)时间、O(n+m+B)空间。
void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> g(n + 1);
    while (m--) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }
    vector<int> vis(n + 1), dis(n + 1);
    LinearBasis t;
    function<void(int)> dfs = [&](int u) {
        vis[u] = 1;
        for (auto [v, w] : g[u])
            if (!vis[v]) {
                dis[v] = dis[u] ^ w;
                dfs(v);
            } else
                t.insert(dis[u] ^ dis[v] ^ w);
    };
    dfs(1);
    cout << t.qur(dis[n]) << '\n';
}

// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// CF118E Bertown Roads
// 原题：https://codeforces.com/problemset/problem/118/E
// 所属知识点：割边；使用模板：LowLink
// 题意：把连通无向图定向为强连通图。
// 转化：存在桥时不可能；无桥时DFS树边向下、返祖边向上可得强连通方向。
// 调用：先run判桥；沿dfn更早到更晚识别树边，另一次DFS每边只定向一次。
// 复杂度：O(n+m)时间与空间。
void solve() {
    int n, m;
    cin >> n >> m;
    LowLink g;
    g.init(n);
    while (m--) {
        int u, v;
        cin >> u >> v;
        g.addedge(u, v);
    }
    g.run();
    for (int b : g.bridge)
        if (b) {
            cout << 0 << '\n';
            return;
        }
    vector<int> vis(n + 1), used(g.edges.size());
    vector<pair<int, int>> ans(g.edges.size());
    function<void(int)> dfs = [&](int u) {
        vis[u] = 1;
        for (auto [v, id] : g.e[u])
            if (!used[id]) {
                used[id] = 1;
                ans[id] = {u, v};
                if (!vis[v])
                    dfs(v);
            }
    };
    dfs(1);
    for (auto [u, v] : ans)
        cout << u << ' ' << v << '\n';
}

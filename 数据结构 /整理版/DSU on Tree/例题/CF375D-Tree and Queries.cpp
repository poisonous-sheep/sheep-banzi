// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// CF375D Tree and Queries
// 原题：https://codeforces.com/contest/375/problem/D
// 所属知识点：DSU on Tree；使用模板：DSUOnTree
// 题意：求子树内至少出现k次的颜色种数。
// 转化：单次颜色频率从x变x+1，只使“至少x+1次”计数增加，删除逆操作；无需树状数组。
// 调用：change对atleast新旧边界加减；answer回答挂在该点的全部询问。
// 复杂度：O(n log n+m)时间、O(n+m+颜色值域)空间。
void solve() {
    int n, m;
    cin >> n >> m;
    DSUOnTree t(n);
    vector<int> c(n + 1), cnt(100001), atleast(n + 1), ans(m);
    for (int i = 1; i <= n; i++)
        cin >> c[i];
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        t.add_edge(u, v);
    }
    vector<vector<pair<int, int>>> q(n + 1);
    for (int i = 0; i < m; i++) {
        int u, k;
        cin >> u >> k;
        q[u].push_back({k, i});
    }
    auto change = [&](int u, int d) {
        int &x = cnt[c[u]];
        if (d == 1)
            atleast[++x]++;
        else
            atleast[x--]--;
    };
    auto answer = [&](int u) {
        for (auto [k, i] : q[u])
            ans[i] = k <= n ? atleast[k] : 0;
    };
    t.run(change, answer);
    for (int x : ans)
        cout << x << '\n';
}

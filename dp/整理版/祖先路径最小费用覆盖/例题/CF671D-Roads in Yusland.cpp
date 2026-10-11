// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// CF671D Roads in Yusland
// 原题：https://codeforces.com/problemset/problem/671/D
// 所属知识点：祖先路径最小费用覆盖；使用模板：AncestorCover
// 题意：给定工人各可修一条祖先路径，付费雇佣工人覆盖所有树边，求最小总费用。
// 转化：把边(parent[x],x)映射为点x。u到v的边集合变成u到v下一层孩子的点路径；忽略u=v的空路径，根用免费单点覆盖。
// 调用：DFS建立fa、倍增表；将v下方孩子作为top，add_path；run_heap。原题n,m≤300000，不能调用O(n²)深度DP。
// 复杂度：O(n log n+(n+m)log(m+1))时间；O(n log n+m)空间。
void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> e(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    AncestorCover t(n);
    int L = 1;
    while ((1LL << L) <= n)
        L++;
    vector<vector<int32_t>> up(L, vector<int32_t>(n + 1));
    function<void(int, int)> dfs = [&](int u, int p) {
        up[0][u] = p;
        for (int k = 1; k < L; k++)
            up[k][u] = up[k - 1][up[k - 1][u]];
        for (int v : e[u])
            if (v != p) {
                t.add_edge(u, v);
                t.dep[v] = t.dep[u] + 1;
                dfs(v, u);
            }
    };
    dfs(1, 0);
    t.add_path(1, 1, 0);
    while (m--) {
        int u, v, c;
        cin >> u >> v >> c;
        if (u == v)
            continue;
        int x = u, d = t.dep[u] - t.dep[v] - 1;
        for (int k = 0; k < L; k++)
            if (d >> k & 1)
                x = up[k][x];
        t.add_path(u, x, c);
    }
    cout << t.run_heap() << '\n';
}

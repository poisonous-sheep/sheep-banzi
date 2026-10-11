// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// CF600E Lomsat gelral
// 原题：https://codeforces.com/problemset/problem/600/E
// 所属知识点：DSU on Tree；使用模板：DSUOnTree
// 题意：求子树众数颜色编号和。
// 转化：DSU保留重子树，颜色增删同时更新每个频率的颜色和与种类数。
// 调用：change维护cnt、freqSum、freqCount及mx；answer读freqSum[mx]。
// 复杂度：O(n log n)时间、O(n+颜色值域)空间。
void solve() {
    int n;
    cin >> n;
    vector<int> c(n + 1), ans(n + 1), cnt(n + 1), fc(n + 1), sum(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> c[i];
    DSUOnTree t(n);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        t.add_edge(u, v);
    }
    int mx = 0;
    auto change = [&](int u, int d) {
        int x = c[u], k = cnt[x];
        if (k)
            fc[k]--, sum[k] -= x;
        k = cnt[x] += d;
        if (k)
            fc[k]++, sum[k] += x;
        mx = max(mx, k);
        while (mx && !fc[mx])
            mx--;
    };
    auto answer = [&](int u) { ans[u] = sum[mx]; };
    t.run(change, answer);
    for (int i = 1; i <= n; i++)
        cout << ans[i] << " \n"[i == n];
}

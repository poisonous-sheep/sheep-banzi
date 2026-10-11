// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// P3469 BLO-Blockade
// 原题：https://www.luogu.com.cn/problem/P3469
// 所属知识点：割点；使用模板：LowLink
// 题意：分别封锁每个点的所有边，统计不连通有序点对。
// 转化：原图连通，删边后分块；总点对减去各块内部点对。
// 调用：利用parts[u]与剩余块n-1-sum(parts)，再加2(n-1)。
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
    for (int u = 1; u <= n; u++) {
        int rest = n - 1, ans = 2 * (n - 1) + (n - 1) * (n - 1);
        for (int s : g.parts[u]) {
            rest -= s;
            ans -= s * s;
        }
        ans -= rest * rest;
        cout << ans << '\n';
    }
}

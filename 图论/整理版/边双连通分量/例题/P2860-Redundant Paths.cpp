// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// P2860 Redundant Paths
// 原题：https://www.luogu.com.cn/problem/P2860
// 所属知识点：边双连通分量；使用模板：LowLink
// 题意：最少加边让任意两点有两条边不重叠路径。
// 转化：缩为桥树后，配对叶子可消除所有桥；答案ceil(叶子数/2)。
// 调用：用原边与bel计算桥树度数，数度1点。
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
    vector<int> d(g.cnt + 1);
    for (auto [u, v] : g.edges)
        if (g.bel[u] != g.bel[v]) {
            d[g.bel[u]]++;
            d[g.bel[v]]++;
        }
    int leaf = 0;
    for (int i = 1; i <= g.cnt; i++)
        leaf += d[i] == 1;
    cout << (leaf + 1) / 2 << '\n';
}

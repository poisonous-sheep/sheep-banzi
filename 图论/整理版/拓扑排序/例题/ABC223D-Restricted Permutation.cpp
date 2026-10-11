// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// ABC223D Restricted Permutation
// 原题：https://atcoder.jp/contests/abc223/tasks/abc223_d
// 所属知识点：拓扑排序；使用模板：Topo
// 题意：给先后约束，求字典序最小排列，无解-1。
// 转化：每步取当前所有零入度点中的最小点。
// 调用：toposort(true)，长度<n判环。
// 复杂度：O((n+m)log n)时间、O(n+m)空间。
void solve() {
    int n, m;
    cin >> n >> m;
    Topo g;
    g.init(n);
    while (m--) {
        int u, v;
        cin >> u >> v;
        g.addedge(u, v);
    }
    auto ans = g.toposort(true);
    if ((int)ans.size() != n) {
        cout << -1 << '\n';
        return;
    }
    for (int i = 0; i < n; i++)
        cout << ans[i] << (i + 1 == n ? '\n' : ' ');
}

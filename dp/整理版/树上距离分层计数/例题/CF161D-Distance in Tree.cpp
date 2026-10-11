// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// CF161D Distance in Tree
// 原题：https://codeforces.com/contest/161/problem/D
// 所属知识点：树上距离分层计数；使用模板：TreeDistanceDP
// 题意：统计距离恰好K的无序点对。
// 转化：每对在LCA合并两条不同子树深度时唯一计入，深度和+1=K。
// 调用：建树后pairs(K)。
// 复杂度：O(nK)时间、O(nK)空间。
void solve() {
    int n, K;
    cin >> n >> K;
    TreeDistanceDP t(n);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        t.add_edge(u, v);
    }
    cout << t.pairs(K) << '\n';
}

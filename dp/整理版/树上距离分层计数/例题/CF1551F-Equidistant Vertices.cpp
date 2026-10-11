// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// CF1551F Equidistant Vertices
// 原题：https://codeforces.com/contest/1551/problem/F
// 所属知识点：树上距离分层计数；使用模板：TreeDistanceDP
// 题意：计数树上大小k的两两等距点集。
// 转化：k>=3时必有唯一中心，所有选点距中心相同且来自不同分支。
// 调用：多测，每组建树后equidistant(k)。
// 复杂度：O(n²k)时间、O(nk)空间。
void solve() {
    int T;
    cin >> T;
    while (T--) {
        int n, k;
        cin >> n >> k;
        TreeDistanceDP t(n);
        for (int i = 1; i < n; i++) {
            int u, v;
            cin >> u >> v;
            t.add_edge(u, v);
        }
        cout << t.equidistant(k) << '\n';
    }
}

// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// HDU4912 Paths on the tree
// 原题：https://acm.hdu.edu.cn/showproblem.php?pid=4912
// 所属知识点：树上不相交给定路径；使用模板：TreePathSelect
// 题意：从给定树上路径中选尽量多条，使所选路径顶点互不相交。
// 转化：把每条路径权重设为1就是同一带权选择问题；原题可用贪心，本例展示通用DP的等权特例。
// 调用：循环到EOF读n,m及树边、路径端点；build，add_path(x,y,1)，run。
// 复杂度：O((n+m)log n)时间、O(n log n+m)空间。
void solve() {
    int n, m;
    while (cin >> n >> m) {
        TreePathSelect t(n);
        for (int i = 1; i < n; i++) {
            int u, v;
            cin >> u >> v;
            t.add_edge(u, v);
        }
        t.build();
        while (m--) {
            int x, y;
            cin >> x >> y;
            t.add_path(x, y, 1);
        }
        cout << t.run() << '\n';
    }
}

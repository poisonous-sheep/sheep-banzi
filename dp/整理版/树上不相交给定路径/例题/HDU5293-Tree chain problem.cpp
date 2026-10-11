// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// HDU5293 Tree chain problem
// 原题：https://acm.hdu.edu.cn/showproblem.php?pid=5293
// 所属知识点：树上不相交给定路径；使用模板：TreePathSelect
// 题意：树上给出带权链，选择顶点互不相交的链使权值和最大。
// 转化：与课堂路径1的点不相交带权模型一致；delta之和扣掉所选路径占用顶点造成的子树最优损失。
// 调用：读T；每组n,m、n-1条边、m条x,y,w；build后add_path，run使用优化版。
// 复杂度：O((n+m)log n)时间、O(n log n+m)空间。
void solve() {
    int T;
    cin >> T;
    while (T--) {
        int n, m;
        cin >> n >> m;
        TreePathSelect t(n);
        for (int i = 1; i < n; i++) {
            int u, v;
            cin >> u >> v;
            t.add_edge(u, v);
        }
        t.build();
        while (m--) {
            int x, y, w;
            cin >> x >> y >> w;
            t.add_path(x, y, w);
        }
        cout << t.run() << '\n';
    }
}

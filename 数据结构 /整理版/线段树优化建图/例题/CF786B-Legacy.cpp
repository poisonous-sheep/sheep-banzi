// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// CF786B Legacy
// 原题：https://codeforces.com/problemset/problem/786/B
// 所属知识点：线段树优化建图；使用模板：SegGraph
// 题意：三类点/区间边，求源点到所有原点的距离。
// 转化：每个区间拆成O(log n)个树节点，保持原图可达与代价。
// 调用：按op1/2/3调用add_edge/add_out/add_in，dijkstra只输出原点。
// 复杂度：O((n+q log n)log n)时间、O(n+q log n)空间。
void solve() {
    int n, q, s;
    cin >> n >> q >> s;
    SegGraph sg(n);
    while (q--) {
        int op, v, l, r, w;
        cin >> op;
        if (op == 1) {
            cin >> v >> l >> w;
            sg.add_edge(v, l, w);
        } else {
            cin >> v >> l >> r >> w;
            if (op == 2)
                sg.add_out(v, l, r, w);
            else
                sg.add_in(l, r, v, w);
        }
    }
    auto d = sg.dijkstra(s);
    for (int i = 1; i <= n; i++)
        cout << (d[i] == INF ? -1 : d[i]) << (i == n ? '\n' : ' ');
}

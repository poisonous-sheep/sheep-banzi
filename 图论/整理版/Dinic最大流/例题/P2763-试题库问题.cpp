// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// P2763 试题库问题
// 原题：https://www.luogu.com.cn/problem/P2763
// 所属知识点：Dinic最大流；使用模板：FlowGraph
// 题意：选题满足各类别需求，每道题最多用一次，输出分配。
// 转化：源到类别为需求，类别到可用题为1，题到汇为1。
// 调用：保存类别到题正向边号；总流达标后残量0的选择边为分配。
// 复杂度：一般O(V^2 E)时间、O(V+E)空间。
void solve() {
    int k, n;
    cin >> k >> n;
    int s = k + n + 1, t = s + 1;
    FlowGraph<int> g;
    g.init(s, t, t);
    int need = 0;
    for (int c = 1, x; c <= k; c++) {
        cin >> x;
        need += x;
        g.addedge(s, c, x);
    }
    vector<array<int, 3>> chosen;
    for (int j = 1; j <= n; j++) {
        int p;
        cin >> p;
        while (p--) {
            int c;
            cin >> c;
            chosen.push_back({c, j, g.etot});
            g.addedge(c, k + j, 1);
        }
        g.addedge(k + j, t, 1);
    }
    if (g.dinic() != need) {
        cout << "No Solution!\n";
        return;
    }
    vector<vector<int>> ans(k + 1);
    for (auto [c, j, id] : chosen)
        if (g.e[id].f == 0)
            ans[c].push_back(j);
    for (int c = 1; c <= k; c++) {
        cout << c << ":";
        for (int j : ans[c])
            cout << ' ' << j;
        cout << '\n';
    }
}

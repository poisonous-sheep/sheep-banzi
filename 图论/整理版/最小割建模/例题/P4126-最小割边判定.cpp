// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// P4126 最小割边判定
// 原题：https://www.luogu.com.cn/problem/P4126
// 所属知识点：最小割建模；使用模板：FlowGraph
// 题意：判断每条边是否可出现在某个或所有最小割中。
// 转化：最大流后残量SCC：饱和且两端不同SCC可属于某割；起点在源SCC且终点在汇SCC属于所有割。
// 调用：dinic后将正残量边加入SCC；按保存原边号检查f=0和col条件。
// 复杂度：最大流一般O(V²E)，SCC O(V+E)，O(V+E)空间。
void solve() {
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    FlowGraph<int> g;
    g.init(s, t, n);
    vector<array<int, 3>> a(m);
    for (auto &z : a) {
        int c;
        cin >> z[0] >> z[1] >> c;
        z[2] = g.etot;
        g.addedge(z[0], z[1], c);
    }
    g.dinic();
    SCC sc;
    sc.init(n);
    for (int u = 1; u <= n; u++)
        for (int i = g.head[u]; i != -1; i = g.e[i].nxt)
            if (g.e[i].f > 0)
                sc.addedge(u, g.e[i].v);
    sc.run();
    for (auto [u, v, id] : a) {
        bool possible = g.e[id].f == 0 && sc.bel[u] != sc.bel[v];
        bool necessary = possible && sc.bel[u] == sc.bel[s] && sc.bel[v] == sc.bel[t];
        cout << possible << ' ' << necessary << '\n';
    }
}

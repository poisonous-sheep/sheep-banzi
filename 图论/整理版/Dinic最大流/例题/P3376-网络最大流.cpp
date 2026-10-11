// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// P3376 网络最大流
// 原题：https://www.luogu.com.cn/problem/P3376
// 所属知识点：Dinic最大流；使用模板：FlowGraph
// 题意：有向容量图求源到汇最大流。
// 转化：每条原边配反向撤销边，Dinic反复分层增广。
// 调用：init(s,t,n)，addedge，dinic。
// 复杂度：O(V^2 E)时间、O(V+E)空间。
void solve() {
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    FlowGraph<int> g;
    g.init(s, t, n);
    while (m--) {
        int u, v, c;
        cin >> u >> v >> c;
        g.addedge(u, v, c);
    }
    cout << g.dinic() << '\n';
}

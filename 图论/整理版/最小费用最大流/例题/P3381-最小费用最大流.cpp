// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// P3381 最小费用最大流
// 原题：https://www.luogu.com.cn/problem/P3381
// 所属知识点：最小费用最大流；使用模板：MinCostFlow
// 题意：有向容量费用网络求最小费用最大流。
// 转化：费用最短的残量增广路保证每个流量阶段费用最小。
// 调用：add_edge(u,v,w,c)，run(s,t)。
// 复杂度：O(AE log V)时间，O(V+E)空间；此题初始c>=0。
void solve() {
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    MinCostFlow g(n);
    while (m--) {
        int u, v, w, c;
        cin >> u >> v >> w >> c;
        g.add_edge(u, v, w, c);
    }
    auto [f, c] = g.run(s, t);
    cout << f << ' ' << c << '\n';
}

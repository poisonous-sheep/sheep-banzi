// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// P6348 Journeys
// 原题：https://www.luogu.com.cn/problem/P6348
// 所属知识点：线段树优化建图；使用模板：SegGraph
// 题意：区间间建立双向通信线路，求起点到各站的最少线路数。
// 转化：区间到辅助点0，辅助点到另一段1；反向另建辅助点。
// 调用：每条线路新增两个点，add_in与add_out组合；Dijkstra求代价。
// 复杂度：O((n+m log n)log(n+m))时间、O(n+m log n)空间。
void solve() {
    int n, m, p;
    cin >> n >> m >> p;
    SegGraph sg(n);
    while (m--) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        int x = ++sg.tot;
        sg.add_in(a, b, x, 0);
        sg.add_out(x, c, d, 1);
        int y = ++sg.tot;
        sg.add_in(c, d, y, 0);
        sg.add_out(y, a, b, 1);
    }
    auto dis = sg.dijkstra(p);
    for (int i = 1; i <= n; i++)
        cout << (dis[i] == INF ? -1 : dis[i]) << '\n';
}

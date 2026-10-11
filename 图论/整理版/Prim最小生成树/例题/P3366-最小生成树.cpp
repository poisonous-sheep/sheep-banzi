// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// P3366 最小生成树
// 原题：https://www.luogu.com.cn/problem/P3366
// 所属知识点：Prim最小生成树；使用模板：Prim
// 题意：求MST，不连通输出orz。
// 转化：无向图跨割最小边贪心满足MST性质。
// 调用：init、addedge、run，先判断bool。
// 复杂度：O(m log m)时间、O(n+m)空间。
void solve() {
    int n, m;
    cin >> n >> m;
    Prim g;
    g.init(n);
    while (m--) {
        int u, v, w;
        cin >> u >> v >> w;
        g.addedge(u, v, w);
    }
    auto [ok, ans] = g.run();
    if (ok)
        cout << ans << '\n';
    else
        cout << "orz\n";
}

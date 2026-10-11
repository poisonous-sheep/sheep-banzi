// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// P8435 点双连通分量
// 原题：https://www.luogu.com.cn/problem/P8435
// 所属知识点：点双连通分量；使用模板：VDCC
// 题意：输出所有点双。
// 转化：直接调用点栈Tarjan。
// 调用：边号0..m-1；run后输出bcc。
// 复杂度：O(n+m)时间与空间。
void solve() {
    int n, m;
    cin >> n >> m;
    VDCC g;
    g.init(n);
    for (int id = 0; id < m; id++) {
        int u, v;
        cin >> u >> v;
        g.addedge(u, v, id);
    }
    g.run();
    cout << g.bcc.size() << '\n';
    for (auto &c : g.bcc) {
        cout << c.size();
        for (int u : c)
            cout << ' ' << u;
        cout << '\n';
    }
}

// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// P8436 边双连通分量
// 原题：https://www.luogu.com.cn/problem/P8436
// 所属知识点：边双连通分量；使用模板：LowLink
// 题意：输出边双数量及每个分量的点。
// 转化：桥分隔分量，删除桥后的连通块就是答案。
// 调用：run后输出bcc。
// 复杂度：O(n+m)时间与空间。
void solve() {
    int n, m;
    cin >> n >> m;
    LowLink g;
    g.init(n);
    while (m--) {
        int u, v;
        cin >> u >> v;
        g.addedge(u, v);
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

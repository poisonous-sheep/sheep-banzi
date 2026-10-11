// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// P3388 割点
// 原题：https://www.luogu.com.cn/problem/P3388
// 所属知识点：割点；使用模板：LowLink
// 题意：输出全部割点。
// 转化：Tarjan low判定去点后有子树无法连回祖先。
// 调用：run遍历非连通图；按cut扫描。
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
    vector<int> ans;
    for (int u = 1; u <= n; u++)
        if (g.cut[u])
            ans.push_back(u);
    cout << ans.size() << '\n';
    for (int u : ans)
        cout << u << ' ';
    cout << '\n';
}

// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// P1656 炸铁路
// 原题：https://www.luogu.com.cn/problem/P1656
// 所属知识点：割边；使用模板：LowLink
// 题意：输出删除后使图不连通的铁路。
// 转化：这正是桥的定义。
// 调用：run后筛bridge，端点排序后按字典序输出。
// 复杂度：O(n+m+k log k)时间、O(n+m)空间。
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
    vector<pair<int, int>> ans;
    for (int i = 0; i < (int)g.edges.size(); i++)
        if (g.bridge[i]) {
            auto [u, v] = g.edges[i];
            if (u > v)
                swap(u, v);
            ans.push_back({u, v});
        }
    sort(ans.begin(), ans.end());
    for (auto [u, v] : ans)
        cout << u << ' ' << v << '\n';
}

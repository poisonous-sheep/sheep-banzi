// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// P2341 受欢迎的牛
// 原题：https://www.luogu.com.cn/problem/P2341
// 所属知识点：Tarjan强连通分量；使用模板：SCC
// 题意：找被所有点可达的点数。
// 转化：缩点DAG唯一出度0分量中的所有点满足；多于一个则无解。
// 调用：run后枚举原边计算分量出度，检查唯一汇分量。
// 复杂度：O(n+m)时间与空间。
void solve() {
    int n, m;
    cin >> n >> m;
    SCC scc;
    scc.init(n);
    vector<pair<int, int>> e(m);
    for (auto &[u, v] : e) {
        cin >> u >> v;
        scc.addedge(u, v);
    }
    scc.run();
    vector<int> out(scc.cnt + 1), sz(scc.cnt + 1);
    for (int u = 1; u <= n; u++)
        sz[scc.bel[u]]++;
    for (auto [u, v] : e)
        if (scc.bel[u] != scc.bel[v])
            out[scc.bel[u]]++;
    int ans = 0, count = 0;
    for (int c = 1; c <= scc.cnt; c++)
        if (!out[c]) {
            count++;
            ans = sz[c];
        }
    cout << (count == 1 ? ans : 0) << '\n';
}

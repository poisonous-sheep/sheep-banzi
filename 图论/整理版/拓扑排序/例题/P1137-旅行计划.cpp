// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// P1137 旅行计划
// 原题：https://www.luogu.com.cn/problem/P1137
// 所属知识点：拓扑排序；使用模板：Topo
// 题意：DAG中每个终点最多经过多少城市。
// 转化：拓扑顺序做最长路，dp[v]=max(dp[v],dp[u]+1)。
// 调用：按toposort遍历，输出每点dp。
// 复杂度：O(n+m)时间与空间。
void solve() {
    int n, m;
    cin >> n >> m;
    Topo g;
    g.init(n);
    while (m--) {
        int u, v;
        cin >> u >> v;
        g.addedge(u, v);
    }
    vector<int> dp(n + 1, 1);
    for (int u : g.toposort())
        for (int v : g.edge[u])
            dp[v] = max(dp[v], dp[u] + 1);
    for (int i = 1; i <= n; i++)
        cout << dp[i] << '\n';
}

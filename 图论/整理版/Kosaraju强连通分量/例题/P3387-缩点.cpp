// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// P3387 缩点
// 原题：https://www.luogu.com.cn/problem/P3387
// 所属知识点：Kosaraju强连通分量；使用模板：Kosaraju
// 题意：有向图走一条路线，点权最多可取得多少；每点只计一次。
// 转化：正权SCC内可遍历全部点，缩为DAG做最长路。
// 调用：run、汇总点权、建立分量边，用Kahn顺序转移dp。
// 复杂度：O(n+m)时间与空间。
void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    Kosaraju scc;
    scc.init(n);
    vector<pair<int, int>> e(m);
    for (auto &[u, v] : e) {
        cin >> u >> v;
        scc.addedge(u, v);
    }
    scc.run();
    int k = scc.cnt;
    vector<int> w(k + 1), deg(k + 1);
    vector<vector<int>> g(k + 1);
    for (int i = 1; i <= n; i++)
        w[scc.bel[i]] += a[i];
    for (auto [u, v] : e) {
        u = scc.bel[u];
        v = scc.bel[v];
        if (u != v) {
            g[u].push_back(v);
            deg[v]++;
        }
    }
    queue<int> q;
    vector<int> dp = w;
    for (int c = 1; c <= k; c++)
        if (!deg[c])
            q.push(c);
    int ans = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        ans = max(ans, dp[u]);
        for (int v : g[u]) {
            dp[v] = max(dp[v], dp[u] + w[v]);
            if (!--deg[v])
                q.push(v);
        }
    }
    cout << ans << '\n';
}

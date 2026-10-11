// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// CF510E Fox And Dinner
// 原题：https://codeforces.com/contest/510/problem/E
// 所属知识点：有上下界可行流与最大流；使用模板：BoundedFlow
// 题意：将年龄数排成若干长度至少3的圆桌，相邻和为素数。
// 转化：年龄>=2使素数边只可能连接奇偶；每点恰好两条选择边，转为上下界为2的二分图度约束。
// 调用：源到奇点[2,2]，素数边[0,1]，偶点到汇[2,2]，汇到源[0,2n]，feasible后value恢复环。
// 复杂度：建边O(n² sqrt A)，最大流一般O(V²E)，O(n²)空间。
void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    int s = n + 1, t = n + 2;
    BoundedFlow g(t);
    vector<array<int, 3>> choice;
    auto prime = [](int x) {
        if (x < 2)
            return false;
        for (int p = 2; p <= x / p; p++)
            if (x % p == 0)
                return false;
        return true;
    };
    for (int i = 1; i <= n; i++)
        if (a[i] & 1)
            g.add_edge(s, i, 2, 2);
        else
            g.add_edge(i, t, 2, 2);
    for (int i = 1; i <= n; i++)
        if (a[i] & 1)
            for (int j = 1; j <= n; j++)
                if (!(a[j] & 1) && prime(a[i] + a[j]))
                    choice.push_back({i, j, g.add_edge(i, j, 0, 1)});
    g.add_edge(t, s, 0, 2 * n);
    if (!g.feasible()) {
        cout << "Impossible\n";
        return;
    }
    vector<vector<int>> adj(n + 1), cycles;
    for (auto [u, v, k] : choice)
        if (g.value(k))
            adj[u].push_back(v), adj[v].push_back(u);
    vector<int> vis(n + 1);
    for (int i = 1; i <= n; i++)
        if (!vis[i]) {
            vector<int> cyc;
            int u = i, p = 0;
            do {
                cyc.push_back(u);
                vis[u] = 1;
                int v = adj[u][0] == p ? adj[u][1] : adj[u][0];
                p = u;
                u = v;
            } while (u != i);
            cycles.push_back(cyc);
        }
    cout << cycles.size() << '\n';
    for (auto c : cycles) {
        cout << c.size();
        for (int u : c)
            cout << ' ' << u;
        cout << '\n';
    }
}

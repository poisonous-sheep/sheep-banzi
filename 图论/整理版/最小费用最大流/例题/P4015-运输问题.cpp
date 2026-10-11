// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// P4015 运输问题
// 原题：https://www.luogu.com.cn/problem/P4015
// 所属知识点：最小费用最大流；使用模板：MinCostFlow
// 题意：运输供需平衡的货物，求最小和最大费用。
// 转化：仓库到商店边的流量代表货运量，负费用后最小值对应最大费用。
// 调用：分别重建正费用、负费用网络；输出run的费用及负号恢复。
// 复杂度：O(VE+AE log V)时间、O(V+E)空间。
void solve() {
    int m, n;
    cin >> m >> n;
    vector<int> a(m + 1), b(n + 1);
    int total = 0;
    for (int i = 1; i <= m; i++)
        cin >> a[i], total += a[i];
    for (int j = 1; j <= n; j++)
        cin >> b[j];
    vector<vector<int>> c(m + 1, vector<int>(n + 1));
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            cin >> c[i][j];
    for (int sign : {1, -1}) {
        int s = m + n + 1, t = s + 1;
        MinCostFlow g(t);
        for (int i = 1; i <= m; i++) {
            g.add_edge(s, i, a[i], 0);
            for (int j = 1; j <= n; j++)
                g.add_edge(i, m + j, total, c[i][j] * sign);
        }
        for (int j = 1; j <= n; j++)
            g.add_edge(m + j, t, b[j], 0);
        cout << g.run(s, t).second * sign << '\n';
    }
}

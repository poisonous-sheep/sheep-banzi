// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// P2762 太空飞行计划问题
// 原题：https://www.luogu.com.cn/problem/P2762
// 所属知识点：最小割建模；使用模板：FlowGraph
// 题意：实验带收益并依赖设备，设备有费用，求最优实验设备集合。
// 转化：选择实验必须选择依赖设备，是最大权闭合子图。
// 调用：收益S->实验，费用设备->T，实验->设备INF；cut_side恢复选点。
// 复杂度：O(V^2 E)时间、O(V+E)空间。
void solve() {
    int m, n;
    cin >> m >> n;
    string line;
    getline(cin, line);
    vector<int> profit(m + 1);
    vector<vector<int>> need(m + 1);
    int total = 0;
    for (int i = 1; i <= m; i++) {
        getline(cin, line);
        istringstream in(line);
        in >> profit[i];
        total += profit[i];
        int x;
        while (in >> x)
            need[i].push_back(x);
    }
    vector<int> cost(n + 1);
    for (int j = 1; j <= n; j++)
        cin >> cost[j];
    int s = m + n + 1, t = s + 1;
    FlowGraph<int> g;
    g.init(s, t, t);
    for (int i = 1; i <= m; i++) {
        g.addedge(s, i, profit[i]);
        for (int j : need[i])
            g.addedge(i, m + j, total + 1);
    }
    for (int j = 1; j <= n; j++)
        g.addedge(m + j, t, cost[j]);
    int ans = total - g.dinic();
    auto vis = g.cut_side();
    for (int i = 1; i <= m; i++)
        if (vis[i])
            cout << i << ' ';
    cout << '\n';
    for (int j = 1; j <= n; j++)
        if (vis[m + j])
            cout << j << ' ';
    cout << '\n' << ans << '\n';
}

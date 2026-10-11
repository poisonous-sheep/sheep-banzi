// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// P2016 战略游戏
// 原题：https://www.luogu.com.cn/problem/P2016
// 所属知识点：二状态树形背包；使用模板：BinaryTreeKnapsack
// 题意：树上选最少士兵，使每条边至少一个端点被选。
// 转化：每点0/1表示放不放，费用0/1；父子都不放的边状态禁止，就是树最小点覆盖。
// 调用：建立有根输入树，cost={0,1}，edge_cost[v][0][0]=INF；run后取最小费用。
// 复杂度：此统一背包版O(n²)时间/空间；只求最小值可去背包维得到O(n)专用DP。
void solve() {
    int n;
    cin >> n;
    BinaryTreeKnapsack t(n);
    vector<vector<int>> e(n + 1);
    for (int z = 0; z < n; z++) {
        int u, k;
        cin >> u >> k;
        u++;
        while (k--) {
            int v;
            cin >> v;
            v++;
            e[u].push_back(v);
            e[v].push_back(u);
        }
    }
    for (int u = 1; u <= n; u++)
        t.cost[u] = {0, 1};
    function<void(int, int)> dfs = [&](int u, int p) {
        for (int v : e[u])
            if (v != p) {
                t.add_edge(u, v);
                t.edge_cost[v][0][0] = t.INF;
                dfs(v, u);
            }
    };
    dfs(1, 0);
    auto ans = t.run(1);
    cout << *min_element(ans.begin(), ans.end()) << '\n';
}

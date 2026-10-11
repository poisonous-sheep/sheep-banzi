// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// P2774 方格取数问题
// 原题：https://www.luogu.com.cn/problem/P2774
// 所属知识点：最小割建模；使用模板：FlowGraph
// 题意：选不相邻的格子，使权值和最大。
// 转化：棋盘二分图最大权独立集=总权-最小点覆盖；冲突边给INF。
// 调用：S到黑格点权，白格到T点权，黑到相邻白INF，输出total-dinic。
// 复杂度：O(V^2 E)时间、O(V+E)空间。
void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(n, vector<int>(m));
    int total = 0;
    for (auto &row : a)
        for (int &x : row) {
            cin >> x;
            total += x;
        }
    int s = n * m + 1, t = s + 1;
    FlowGraph<int> g;
    g.init(s, t, t);
    int dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, 1, -1};
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            int u = i * m + j + 1;
            if ((i + j) % 2 == 0) {
                g.addedge(s, u, a[i][j]);
                for (int k = 0; k < 4; k++) {
                    int x = i + dx[k], y = j + dy[k];
                    if (0 <= x && x < n && 0 <= y && y < m)
                        g.addedge(u, x * m + y + 1, total + 1);
                }
            } else
                g.addedge(u, t, a[i][j]);
        }
    cout << total - g.dinic() << '\n';
}

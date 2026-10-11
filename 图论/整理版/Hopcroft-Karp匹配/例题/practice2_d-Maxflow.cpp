// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// practice2_d Maxflow
// 原题：https://atcoder.jp/contests/practice2/tasks/practice2_d
// 所属知识点：Hopcroft-Karp匹配；使用模板：HK
// 题意：障碍格盘上放最多1x2骨牌，并输出方案。
// 转化：棋盘黑白染色后每个骨牌是一条二分图匹配边。
// 调用：空白相邻格add；matching后从ml恢复箭头。
// 复杂度：HK为O(E sqrt V)时间、O(V+E)空间。
void solve() {
    int n, m;
    cin >> n >> m;
    vector<string> a(n);
    for (auto &s : a)
        cin >> s;
    HK hk;
    hk.init(n * m, n * m);
    int dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, 1, -1};
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (a[i][j] == '.' && (i + j) % 2 == 0)
                for (int k = 0; k < 4; k++) {
                    int x = i + dx[k], y = j + dy[k];
                    if (0 <= x && x < n && 0 <= y && y < m && a[x][y] == '.')
                        hk.add(i * m + j + 1, x * m + y + 1);
                }
    cout << hk.matching() << '\n';
    for (int u = 1; u <= n * m; u++)
        if (hk.ml[u]) {
            int v = hk.ml[u], x = (u - 1) / m, y = (u - 1) % m, p = (v - 1) / m,
                q = (v - 1) % m;
            if (x == p) {
                a[x][min(y, q)] = '>';
                a[x][max(y, q)] = '<';
            } else {
                a[min(x, p)][y] = 'v';
                a[max(x, p)][y] = '^';
            }
        }
    for (auto &s : a)
        cout << s << '\n';
}

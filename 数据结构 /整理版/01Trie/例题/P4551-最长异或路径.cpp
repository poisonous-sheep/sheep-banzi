// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// P4551 最长异或路径
// 原题：https://www.luogu.com.cn/problem/P4551
// 所属知识点：01Trie；使用模板：Trie
// 题意：树上找边权异或最大的路径。
// 转化：两点路径异或等于根到两点的前缀异或之xor，将所有前缀放入Trie。
// 调用：DFS计算前缀；update每个前缀，再qur求最大。
// 复杂度：O(nB)时间、O(nB)空间。
void solve() {
    int n;
    cin >> n;
    vector<vector<pair<int, int>>> e(n + 1);
    for (int i = 1, u, v, w; i < n; i++) {
        cin >> u >> v >> w;
        e[u].push_back({v, w});
        e[v].push_back({u, w});
    }
    vector<int> d(n + 1);
    function<void(int, int)> dfs = [&](int u, int fa) {
        for (auto [v, w] : e[u])
            if (v != fa) {
                d[v] = d[u] ^ w;
                dfs(v, u);
            }
    };
    dfs(1, 0);
    Trie tr(30);
    for (int i = 1; i <= n; i++)
        tr.update(d[i]);
    int ans = 0;
    for (int i = 1; i <= n; i++)
        ans = max(ans, tr.qur(d[i]));
    cout << ans << '\n';
}

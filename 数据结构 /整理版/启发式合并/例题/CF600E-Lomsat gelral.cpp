// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// CF600E Lomsat gelral
// 原题：https://codeforces.com/problemset/problem/600/E
// 所属知识点：启发式合并；使用模板：SmallMerge
// 题意：对每棵子树求出现最多的颜色的编号和。
// 转化：子树统计是孩子容器的并集；小map并入大map并维护频率最大值。
// 调用：每点insert自身颜色，DFS后merge孩子；合并后记录sum。
// 复杂度：O(n log² n)时间、O(n)活动数据与递归空间。
void solve() {
    int n;
    cin >> n;
    vector<int> c(n + 1), ans(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> c[i];
    vector<vector<int>> g(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<SmallMerge::info> f(n + 1);
    function<void(int, int)> dfs = [&](int u, int p) {
        SmallMerge::insert(f[u], c[u], 1);
        for (int v : g[u])
            if (v != p) {
                dfs(v, u);
                SmallMerge::merge(f[u], f[v]);
            }
        ans[u] = f[u].sum;
    };
    dfs(1, 0);
    for (int i = 1; i <= n; i++)
        cout << ans[i] << " \n"[i == n];
}

// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// ABC120D Decayed Bridges
// 原题：https://atcoder.jp/contests/abc120/tasks/abc120_d
// 所属知识点：并查集；使用模板：DSU
// 题意：按顺序删桥，输出每次删除后的不连通点对数。
// 转化：逆序变成加边；合并大小a,b的块减少a*b对。
// 调用：从空图开始，先记答案，读取size后merge。
// 复杂度：O((n+m)alpha(n))时间、O(n+m)空间。
void solve() {
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> e(m);
    for (auto &[u, v] : e)
        cin >> u >> v;
    DSU dsu(n);
    vector<int> ans(m);
    int cur = n * (n - 1) / 2;
    for (int i = m - 1; i >= 0; i--) {
        ans[i] = cur;
        auto [u, v] = e[i];
        if (!dsu.same(u, v)) {
            cur -= dsu.size(u) * dsu.size(v);
            dsu.merge(u, v);
        }
    }
    for (int x : ans)
        cout << x << '\n';
}

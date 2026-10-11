// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// P3379 最近公共祖先
// 原题：https://www.luogu.com.cn/problem/P3379
// 所属知识点：倍增LCA；使用模板：LCA
// 题意：指定根，回答LCA。
// 转化：读入树并按指定根预处理倍增表。
// 调用：init、addedge、build(s)、lca。
// 复杂度：O((n+q)log n)时间、O(n log n)空间。
void solve() {
    int n, q, s;
    cin >> n >> q >> s;
    LCA tr;
    tr.init(n);
    for (int i = 1, u, v; i < n; i++) {
        cin >> u >> v;
        tr.addedge(u, v);
    }
    tr.build(s);
    while (q--) {
        int u, v;
        cin >> u >> v;
        cout << tr.lca(u, v) << '\n';
    }
}

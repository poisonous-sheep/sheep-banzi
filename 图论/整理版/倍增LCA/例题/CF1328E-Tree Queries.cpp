// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// CF1328E Tree Queries
// 原题：https://codeforces.com/problemset/problem/1328/E
// 所属知识点：倍增LCA；使用模板：LCA
// 题意：若干点各自至多向父移动一次，能否落在同一条根到某点路径上。
// 转化：把点移到父后，所有点需成为最深点的祖先；用LCA判祖先。
// 调用：根的父替换为自身；取最深点v，检查lca(u,v)==u。
// 复杂度：O(n log n+总查询点数log n)时间、O(n log n)空间。
void solve() {
    int n, q;
    cin >> n >> q;
    LCA tr;
    tr.init(n);
    for (int i = 1, u, v; i < n; i++) {
        cin >> u >> v;
        tr.addedge(u, v);
    }
    tr.build();
    while (q--) {
        int k;
        cin >> k;
        vector<int> a(k);
        int v = 1;
        for (int &u : a) {
            cin >> u;
            if (tr.dep[u] > tr.dep[v])
                v = u;
        }
        bool ok = true;
        for (int u : a) {
            u = u == 1 ? 1 : tr.fa[0][u];
            if (tr.lca(u, v) != u)
                ok = false;
        }
        cout << (ok ? "YES" : "NO") << '\n';
    }
}

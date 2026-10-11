// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// practice2_a Disjoint Set Union
// 原题：https://atcoder.jp/contests/practice2/tasks/practice2_a
// 所属知识点：并查集；使用模板：DSU
// 题意：加无向边或询问两点是否连通。
// 转化：加边只会合并连通块，适用普通DSU。
// 调用：0操作merge，1操作same；题目点号0-based。
// 复杂度：O((n+q)alpha(n))时间、O(n)空间。
void solve() {
    int n, q;
    cin >> n >> q;
    DSU dsu(n);
    while (q--) {
        int op, u, v;
        cin >> op >> u >> v;
        if (!op)
            dsu.merge(u, v);
        else
            cout << dsu.same(u, v) << '\n';
    }
}

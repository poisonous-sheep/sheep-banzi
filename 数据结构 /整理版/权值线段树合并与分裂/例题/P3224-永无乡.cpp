// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// P3224 永无乡
// 原题：https://www.luogu.com.cn/problem/P3224
// 所属知识点：权值线段树合并与分裂；使用模板：WeightSegForest
// 题意：合并岛屿，查询连通块内重要度第k小的岛编号。
// 转化：DSU维护块代表；每块一棵权值树，合并时破坏性merge。
// 调用：建立排名到编号映射；DSU合并前取两根，合并后挂到新代表。
// 复杂度：总合并访问量按节点计，查询O(log n)；空间O(n log n)。
void solve() {
    int n, m;
    cin >> n >> m;
    DSU dsu(n);
    WeightSegForest seg(1, n);
    vector<int> root(n + 1), id(n + 1);
    for (int i = 1, x; i <= n; i++) {
        cin >> x;
        id[x] = i;
        root[i] = seg.change(0, x, 1);
    }
    auto join = [&](int x, int y) {
        x = dsu.root(x);
        y = dsu.root(y);
        if (x == y)
            return;
        int r = seg.merge(root[x], root[y]);
        root[x] = root[y] = 0;
        dsu.merge(x, y);
        root[dsu.root(x)] = r;
    };
    while (m--) {
        int u, v;
        cin >> u >> v;
        join(u, v);
    }
    int q;
    cin >> q;
    while (q--) {
        char op;
        int x, y;
        cin >> op >> x >> y;
        if (op == 'B')
            join(x, y);
        else {
            int r = root[dsu.root(x)];
            if (y > seg.size(r))
                cout << -1 << '\n';
            else
                cout << id[seg.kth(r, seg.size(r) - y + 1)] << '\n';
        }
    }
}

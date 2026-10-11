// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// P5494 线段树分裂
// 原题：https://www.luogu.com.cn/problem/P5494
// 所属知识点：权值线段树合并与分裂；使用模板：WeightSegForest
// 题意：维护多个集合，按值域拆分、合并、加频率和排名查询。
// 转化：按<x和>y的次数切排名，将中间值域移到新根。
// 调用：两次split；merge两侧；所有变根操作接收返回值。
// 复杂度：分裂/更新/查询O(log n)，合并按节点交叠计；空间O((n+m)log n)。
void solve() {
    int n, m;
    cin >> n >> m;
    WeightSegForest seg(1, n);
    vector<int> root(m + 2);
    int tot = 1;
    for (int i = 1, c; i <= n; i++) {
        cin >> c;
        if (c)
            root[1] = seg.change(root[1], i, c);
    }
    while (m--) {
        int op, p;
        cin >> op >> p;
        if (op == 0) {
            int x, y;
            cin >> x >> y;
            int c = seg.qur(root[p], 1, x - 1);
            auto [low, high] = seg.split(root[p], seg.size(root[p]) - c);
            int hi = seg.qur(high, y + 1, n);
            auto [mid, upper] = seg.split(high, hi);
            root[p] = seg.merge(low, upper);
            root[++tot] = mid;
        } else if (op == 1) {
            int t;
            cin >> t;
            root[p] = seg.merge(root[p], root[t]);
            root[t] = 0;
        } else if (op == 2) {
            int x, q;
            cin >> x >> q;
            if (x)
                root[p] = seg.change(root[p], q, x);
        } else if (op == 3) {
            int x, y;
            cin >> x >> y;
            cout << seg.qur(root[p], x, y) << '\n';
        } else {
            int k;
            cin >> k;
            if (k <= 0 || k > seg.size(root[p]))
                cout << -1 << '\n';
            else
                cout << seg.kth(root[p], seg.size(root[p]) - k + 1) << '\n';
        }
    }
}

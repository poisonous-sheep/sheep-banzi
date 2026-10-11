// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// P3372 线段树1
// 原题：https://www.luogu.com.cn/problem/P3372
// 所属知识点：区间加线段树；使用模板：SegTree
// 题意：区间加和区间求和。
// 转化：标记可累加，区间和的变化等于增量乘长度。
// 调用：build后将1操作映射modify，2操作映射qur。
// 复杂度：O((n+m)log n)时间、O(n)空间。
void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    SegTree seg;
    seg.build(a);
    while (m--) {
        int op, l, r, k;
        cin >> op >> l >> r;
        if (op == 1) {
            cin >> k;
            seg.modify(l, r, {k});
        } else
            cout << seg.qur(l, r) << '\n';
    }
}

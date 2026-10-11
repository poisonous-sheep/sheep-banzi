// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// P4145 花神游历各国
// 原题：https://www.luogu.com.cn/problem/P4145
// 所属知识点：势能线段树；使用模板：SegTree
// 题意：区间开方或区间和。
// 转化：max<=1的节点所有值已稳定，可停止递归。
// 调用：op0调用update_sqrt，op1调用qur；先交换反向端点。
// 复杂度：累计O(n log log A log n+m log n)时间、O(n)空间。
void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    SegTree seg;
    seg.build(a);
    int m;
    cin >> m;
    while (m--) {
        int op, l, r;
        cin >> op >> l >> r;
        if (l > r)
            swap(l, r);
        if (!op)
            seg.update_sqrt(l, r);
        else
            cout << seg.qur(l, r).sum << '\n';
    }
}

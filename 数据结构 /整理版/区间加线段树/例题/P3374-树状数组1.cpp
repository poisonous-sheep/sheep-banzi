// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// P3374 树状数组1
// 原题：https://www.luogu.com.cn/problem/P3374
// 所属知识点：区间加线段树；使用模板：SegTree
// 题意：单点增加，查询区间和。
// 转化：单点是长度1的区间修改，直接复用懒标记板子。
// 调用：modify(x,x,{k})；qur(x,y)。
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
        int op, x, y;
        cin >> op >> x >> y;
        if (op == 1)
            seg.modify(x, x, {y});
        else
            cout << seg.qur(x, y) << '\n';
    }
}

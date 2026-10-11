// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// P1816 忠诚
// 原题：https://www.luogu.com.cn/problem/P1816
// 所属知识点：普通线段树；使用模板：SegTree
// 题意：询问多段账目中的最小金额。
// 转化：区间最小值满足结合律，建树后直接查询。
// 调用：build(a)，每个区间qur(l,r).mn。
// 复杂度：O(n+q log n)时间、O(n)空间。
void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    SegTree seg;
    seg.build(a);
    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << seg.qur(l, r).mn << (q ? ' ' : '\n');
    }
}

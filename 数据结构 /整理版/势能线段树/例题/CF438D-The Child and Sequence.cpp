// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// CF438D The Child and Sequence
// 原题：https://codeforces.com/problemset/problem/438/D
// 所属知识点：势能线段树；使用模板：SegTree
// 题意：区间和、区间取模、单点赋值。
// 转化：a%x只有在a>=x时改变，并且改变后小于原值一半。
// 调用：modify_mod用区间max剪枝；赋值change恢复势能。
// 复杂度：摊还O((n+m)log A log n)时间、O(n)空间。
void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    SegTree seg;
    seg.build(a);
    while (m--) {
        int op, l, r, x;
        cin >> op;
        if (op == 3) {
            cin >> l >> x;
            seg.change(l, x);
        } else {
            cin >> l >> r;
            if (op == 1)
                cout << seg.qur(l, r).sum << '\n';
            else {
                cin >> x;
                seg.modify_mod(l, r, x);
            }
        }
    }
}

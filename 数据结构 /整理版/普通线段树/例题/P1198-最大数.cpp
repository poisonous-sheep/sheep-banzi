// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// P1198 最大数
// 原题：https://www.luogu.com.cn/problem/P1198
// 所属知识点：普通线段树；使用模板：SegTree
// 题意：在线追加数，查询末尾L个数的最大值；追加依赖上次答案。
// 转化：把追加视为预留数组上的单点赋值，查询变为后缀区间最大值。
// 调用：预留M个位置build；change(++len,x)，qur(len-L+1,len)。
// 复杂度：O(M log M)时间、O(M)空间。
// 变体修改：只将info的min合并改为max；成员mn沿用原名表示最大值。
void solve() {
    int m, d;
    cin >> m >> d;
    vector<int> a(m + 1, LLONG_MIN);
    SegTree seg;
    seg.build(a);
    int len = 0, last = 0;
    while (m--) {
        char op;
        int x;
        cin >> op >> x;
        if (op == 'A') {
            int v = ((__int128)x + last) % d;
            if (v < 0)
                v += d;
            seg.change(++len, v);
        } else {
            last = seg.qur(len - x + 1, len).mn;
            cout << last << '\n';
        }
    }
}

// 依赖：../权值线段树（动态开点基础版）.cpp 中的 WeightSegTree。
// 这是 solve 片段；替换模板的 solve 后再编译，保留模板的 signed main。
// 题号/名称：AtCoder ABC253 C - Max - Min Query
// 原题：https://atcoder.jp/contests/abc253/tasks/abc253_c
// 知识点：权值线段树；动态可重集合、批量删除、最值。
// 题目核心：增删集合元素，询问最大值与最小值之差。
// 转化思路：叶子维护次数，删除 min(c, 当前次数)，最大/小值为第1大/小。
// 模板使用：change、qur(x,x).cnt、kth(1)、kth_max(1)。
// 复杂度：O(Q log V) 时间、O(D log V) 空间；V=1e9+1，D为累计不同插入值数。
void solve() {
    int q;
    cin >> q;
    WeightSegTree seg(0, 1000000000);
    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int x;
            cin >> x;
            seg.change(x, {1});
        } else if (op == 2) {
            int x, c;
            cin >> x >> c;
            int del = min(c, seg.qur(x, x).cnt);
            if (del) seg.change(x, {-del}); // 没有该元素时不调用 change(x,{0})
        } else {
            // 原题保证此时非空；重复元素会占据多个排名。
            cout << seg.kth_max(1) - seg.kth(1) << '\n';
        }
    }
}

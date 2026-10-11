// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// ABC253C Max-Min Query
// 原题：https://atcoder.jp/contests/abc253/tasks/abc253_c
// 所属知识点：动态开点权值线段树；使用模板：WeightSegTree
// 题意：增删元素，查询最大值与最小值之差。
// 转化：次数叶子可批量删除，最值是排名端点。
// 调用：先查次数再change；kth(1)、kth_max(1)。
// 复杂度：O(Q log V)时间、O(D log V)空间。
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
            if (del)
                seg.change(x, {-del}); // 没有该元素时不调用 change(x,{0})
        } else {
            // 原题保证此时非空；重复元素会占据多个排名。
            cout << seg.kth_max(1) - seg.kth(1) << '\n';
        }
    }
}

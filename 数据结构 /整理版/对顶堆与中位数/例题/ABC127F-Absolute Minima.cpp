// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// ABC127F Absolute Minima
// 原题：https://atcoder.jp/contests/abc127/tasks/abc127_f
// 所属知识点：对顶堆与中位数；使用模板：Mid
// 题意：不断加入|x-a|+b，查询使函数最小的最小x及最小值。
// 转化：最小x是下中位数；常数b单独累加。
// 调用：add(a)，查询mid()和cost()+常数和。
// 复杂度：O(q log q)时间、O(q)空间。
void solve() {
    int q;
    cin >> q;
    Mid st;
    int bsum = 0;
    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int a, b;
            cin >> a >> b;
            st.add(a);
            bsum += b;
        } else
            cout << st.mid() << ' ' << st.cost() + bsum << '\n';
    }
}

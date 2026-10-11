// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// P3369 普通平衡树
// 原题：https://www.luogu.com.cn/problem/P3369
// 所属知识点：动态开点权值线段树；使用模板：WeightSegTree
// 题意：可重集合的六种有序操作。
// 转化：次数前缀可转化为排名和严格前驱后继。
// 调用：change增删；qur计数；kth输出排名值。
// 复杂度：O(Q log V)时间、O(D log V)空间。
void solve() {
    int n;
    cin >> n;
    const int L = -10000000, R = 10000000;
    WeightSegTree seg(L, R);
    while (n--) {
        int op, x;
        cin >> op >> x;
        if (op == 1)
            seg.change(x, {1});
        else if (op == 2)
            seg.change(x, {-1});
        else if (op == 3)
            cout << seg.qur(L, x - 1).cnt + 1 << '\n';
        else if (op == 4)
            cout << seg.kth(x) << '\n';
        else if (op == 5) {
            int cnt = seg.qur(L, x - 1).cnt;
            cout << seg.kth(cnt) << '\n';
        } else {
            int cnt = seg.qur(L, x).cnt;
            cout << seg.kth(cnt + 1) << '\n';
        }
        // 原题保证第k小、前驱、后继答案存在；删除须满足集合操作前提。
    }
}

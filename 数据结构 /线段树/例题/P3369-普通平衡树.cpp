// 依赖：../权值线段树（动态开点基础版）.cpp 中的 WeightSegTree。
// 这是 solve 片段；替换模板的 solve 后再编译，保留模板的 signed main。
// 题号/名称：洛谷 P3369 【模板】普通平衡树
// 原题：https://www.luogu.com.cn/problem/P3369
// 知识点：权值线段树；动态排名、第 k 小、严格前驱/后继。
// 题目核心：维护可重集合，实现六类增删和有序查询。
// 转化思路：小于x的数量决定排名/前驱排名，小于等于x的数量决定后继排名。
// 模板使用：change、qur、kth；保留动态开点，值域允许负数。
// 复杂度：O(n log V) 时间、O(D log V) 空间；V=20000001，D为累计不同插入值数。
void solve() {
    int n;
    cin >> n;
    const int L = -10000000, R = 10000000;
    WeightSegTree seg(L, R);
    while (n--) {
        int op, x;
        cin >> op >> x;
        if (op == 1) seg.change(x, {1});
        else if (op == 2) seg.change(x, {-1});
        else if (op == 3) cout << seg.qur(L, x - 1).cnt + 1 << '\n';
        else if (op == 4) cout << seg.kth(x) << '\n';
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

// 依赖：../权值线段树（动态开点基础版）.cpp 中的 WeightSegTree。
// 这是 solve 片段；替换模板的 solve 后再编译，保留模板的 signed main。
// 题号/名称：AtCoder ABC241 D - Sequence Query
// 原题：https://atcoder.jp/contests/abc241/tasks/abc241_d
// 知识点：权值线段树；区间限制的排名查询 + 大值域离散化。
// 题目核心：插入x，查 <=x 的第k大或 >=x 的第k小，不足k个输出-1。
// 转化思路：离线收集所有x并压缩（含查询阈值）；操作仍按原顺序执行。
// 模板使用：change、qur、size、kth；kth返回压缩下标，必须映射回原值。
// 复杂度：O(Q log Q) 时间、O(Q) 空间；压缩值域树最多约2M个节点，M<=Q。
void solve() {
    int q;
    cin >> q;
    vector<array<int, 3>> ask(q);
    vector<int> a;
    for (auto &v : ask) {
        cin >> v[0] >> v[1];
        v[2] = 0;
        if (v[0] != 1) cin >> v[2];
        a.push_back(v[1]);
    }
    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());
    int m = a.size();
    WeightSegTree seg(1, m);
    for (auto [op, x, k] : ask) {
        int pos = lower_bound(a.begin(), a.end(), x) - a.begin() + 1;
        if (op == 1) seg.change(pos, {1});
        else if (op == 2) {
            int cnt = seg.qur(1, pos).cnt;
            if (cnt < k) cout << -1 << '\n';
            else cout << a[seg.kth(cnt - k + 1) - 1] << '\n';
        } else {
            int cnt = seg.qur(1, pos - 1).cnt;
            if (seg.size() - cnt < k) cout << -1 << '\n';
            else cout << a[seg.kth(cnt + k) - 1] << '\n';
        }
    }
}

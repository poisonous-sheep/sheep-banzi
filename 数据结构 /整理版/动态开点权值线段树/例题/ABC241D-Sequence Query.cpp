// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// ABC241D Sequence Query
// 原题：https://atcoder.jp/contests/abc241/tasks/abc241_d
// 所属知识点：动态开点权值线段树；使用模板：WeightSegTree
// 题意：查询<=x的第k大或>=x的第k小。
// 转化：离散化1e18值域，将限制排名映射到全局排名。
// 调用：离线收集阈值；按原顺序change/qur/kth并映射回原值。
// 复杂度：O(Q log Q)时间、O(Q)空间。
void solve() {
    int q;
    cin >> q;
    vector<array<int, 3>> ask(q);
    vector<int> a;
    for (auto &v : ask) {
        cin >> v[0] >> v[1];
        v[2] = 0;
        if (v[0] != 1)
            cin >> v[2];
        a.push_back(v[1]);
    }
    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());
    int m = a.size();
    WeightSegTree seg(1, m);
    for (auto [op, x, k] : ask) {
        int pos = lower_bound(a.begin(), a.end(), x) - a.begin() + 1;
        if (op == 1)
            seg.change(pos, {1});
        else if (op == 2) {
            int cnt = seg.qur(1, pos).cnt;
            if (cnt < k)
                cout << -1 << '\n';
            else
                cout << a[seg.kth(cnt - k + 1) - 1] << '\n';
        } else {
            int cnt = seg.qur(1, pos - 1).cnt;
            if (seg.size() - cnt < k)
                cout << -1 << '\n';
            else
                cout << a[seg.kth(cnt + k) - 1] << '\n';
        }
    }
}

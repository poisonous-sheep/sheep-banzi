// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// CF906D Power Tower
// 原题：https://codeforces.com/problemset/problem/906/D
// 所属知识点：扩展欧拉与指数塔；使用模板：PowerTower
// 题意：数组上给区间，求该区间指数塔模固定m。
// 转化：区间长度可大，但phi链很短；底数为1时cap直接结束。
// 调用：init(a)，每问qur(l,r,m)。
// 复杂度：预处理phi链，查询沿短链与阈值递归；空间O(n+log m)。
void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    PowerTower tr;
    tr.init(a);
    int q;
    cin >> q;
    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << tr.qur(l, r, m) << '\n';
    }
}

// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// P1330 封锁阳光大学
// 原题：https://www.luogu.com.cn/problem/P1330
// 所属知识点：二分图染色；使用模板：BipColor
// 题意：选择点封锁边，并要求相连点不能同时被选，最少选多少。
// 转化：每条边恰有一端被选，每个块只能选二分图的一侧；取较小侧。
// 调用：run判奇环，无解Impossible；累加min(cnt[0],cnt[1])。
// 复杂度：O(n+m)时间与空间。
void solve() {
    int n, m;
    cin >> n >> m;
    BipColor g;
    g.init(n);
    while (m--) {
        int u, v;
        cin >> u >> v;
        g.addedge(u, v);
    }
    if (!g.run()) {
        cout << "Impossible\n";
        return;
    }
    int ans = 0;
    for (auto c : g.cnt)
        ans += min(c[0], c[1]);
    cout << ans << '\n';
}

// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// P3225 矿场搭建
// 原题：https://www.luogu.com.cn/problem/P3225
// 所属知识点：点双连通分量；使用模板：VDCC
// 题意：设置最少出口，保证任一矿点坍塌后仍可逃离，统计方案数。
// 转化：块无割点需2出口；叶子块有1割点需在非割点中选1出口。
// 调用：按边中出现的编号建图，run后逐bcc统计cut数并乘方案。
// 复杂度：O(n+m)时间与空间，方案数按题目保证使用unsigned long long。
void solve() {
    int m, tc = 0;
    while (cin >> m && m) {
        vector<pair<int, int>> e(m);
        int n = 0;
        for (auto &[u, v] : e) {
            cin >> u >> v;
            n = max(n, max(u, v));
        }
        VDCC g;
        g.init(n);
        vector<int> present(n + 1);
        for (int i = 0; i < m; i++) {
            auto [u, v] = e[i];
            present[u] = present[v] = 1;
            g.addedge(u, v, i);
        }
        g.run();
        int need = 0;
        unsigned long long ways = 1;
        for (auto &c : g.bcc) {
            if (!present[c[0]])
                continue;
            int cuts = 0;
            for (int u : c)
                cuts += g.cut[u];
            int s = c.size();
            if (cuts == 0) {
                need += 2;
                ways *= 1ULL * s * (s - 1) / 2;
            } else if (cuts == 1) {
                need++;
                ways *= s - 1;
            }
        }
        cout << "Case " << ++tc << ": " << need << ' ' << ways << '\n';
    }
}

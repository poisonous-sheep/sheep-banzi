#include <bits/stdc++.h>
using namespace std;
#define int long long

// Kruskal重构树：按权值排序建立连通块合并历史；支持不连通森林与LCA瓶颈查询。
// 排序O(m log m)，建树与倍增O(n log n+m alpha(n))的通常界；当前重构树代表递归find可有长链，空间O(n log n+m)。
struct KruskalTree {
    struct edge {
        int u, v, w;
    };
    int n, tot, LOG;
    vector<int> fa, val, dep, bel;
    vector<vector<int>> tr, up;
    vector<edge> e;
    void init(int n_) {
        n = n_;
        tot = n;
        e.clear();
        fa.resize(2 * n + 1);
        iota(fa.begin(), fa.end(), 0);
        val.assign(2 * n + 1, 0);
        tr.assign(2 * n + 1, {});
        dep.assign(2 * n + 1, 0);
        bel.assign(2 * n + 1, 0);
        LOG = 1;
        while ((1LL << LOG) <= 2 * n)
            LOG++;
        up.assign(LOG, vector<int>(2 * n + 1));
    }
    int find(int x) {
        return fa[x] == x ? x : fa[x] = find(fa[x]);
    }
    void addedge(int u, int v, int w) {
        e.push_back({u, v, w});
    }
    void dfs(int u, int f, int component) {
        up[0][u] = f;
        dep[u] = dep[f] + 1;
        bel[u] = component;
        for (int j = 1; j < LOG; j++)
            up[j][u] = up[j - 1][up[j - 1][u]];
        for (int v : tr[u])
            dfs(v, u, component);
    }
    void build(bool maximum = false) {
        sort(e.begin(), e.end(),
             [&](edge a, edge b) { return maximum ? a.w > b.w : a.w < b.w; });
        for (auto [u, v, w] : e) {
            int x = find(u), y = find(v);
            if (x == y)
                continue;
            ++tot;
            val[tot] = w;
            tr[tot] = {x, y};
            fa[x] = fa[y] = tot;
        }
        for (int u = 1; u <= tot; u++)
            if (fa[u] == u)
                dfs(u, 0, u);
    }
    int lca(int u, int v) {
        if (bel[u] != bel[v])
            return 0;
        if (dep[u] < dep[v])
            swap(u, v);
        int d = dep[u] - dep[v];
        for (int j = 0; j < LOG; j++)
            if (d >> j & 1)
                u = up[j][u];
        if (u == v)
            return u;
        for (int j = LOG - 1; j >= 0; j--)
            if (up[j][u] != up[j][v]) {
                u = up[j][u];
                v = up[j][v];
            }
        return up[0][u];
    }
    int qur(int u, int v) {
        int p = lca(u, v);
        return p ? val[p] : -1;
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    KruskalTree tr;
    tr.init(n);
    while (m--) {
        int u, v, w;
        cin >> u >> v >> w;
        tr.addedge(u, v, w);
    }
    tr.build(false);
    int q;
    cin >> q;
    while (q--) {
        int u, v;
        cin >> u >> v;
        int p = tr.lca(u, v);
        if (!p)
            cout << "impossible\n";
        else
            cout << tr.val[p] << '\n';
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;
    while (t--)
        solve();
    return 0;
}

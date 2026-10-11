#include <bits/stdc++.h>
using namespace std;
#define int long long

// 倍增LCA：有根树最近公共祖先与边数距离；1-based，0为虚祖先。
// 预处理O(n log n)，查询O(log n)，空间O(n log n)。
struct LCA {
    int n, LOG;
    vector<vector<int>> e, fa;
    vector<int> dep;
    void init(int n_) {
        n = n_;
        LOG = 1;
        while ((1LL << LOG) <= n)
            LOG++;
        e.assign(n + 1, {});
        fa.assign(LOG, vector<int>(n + 1));
        dep.assign(n + 1, 0);
    }
    void addedge(int u, int v) {
        e[u].push_back(v);
        e[v].push_back(u);
    }
    void dfs(int u, int f) {
        fa[0][u] = f;
        dep[u] = dep[f] + 1;
        for (int j = 1; j < LOG; j++)
            fa[j][u] = fa[j - 1][fa[j - 1][u]];
        for (int v : e[u])
            if (v != f)
                dfs(v, u);
    }
    void build(int root = 1) {
        dfs(root, 0);
    }
    int lca(int u, int v) {
        if (dep[u] < dep[v])
            swap(u, v);
        int d = dep[u] - dep[v];
        for (int j = 0; j < LOG; j++)
            if (d >> j & 1)
                u = fa[j][u];
        if (u == v)
            return u;
        for (int j = LOG - 1; j >= 0; j--)
            if (fa[j][u] != fa[j][v]) {
                u = fa[j][u];
                v = fa[j][v];
            }
        return fa[0][u];
    }
    int distance(int u, int v) {
        int p = lca(u, v);
        return dep[u] + dep[v] - 2 * dep[p];
    }
};

void solve() {
    int n, q, s;
    cin >> n >> q >> s;
    LCA tr;
    tr.init(n);
    for (int i = 1, u, v; i < n; i++) {
        cin >> u >> v;
        tr.addedge(u, v);
    }
    tr.build(s);
    while (q--) {
        int u, v;
        cin >> u >> v;
        cout << tr.lca(u, v) << '\n';
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

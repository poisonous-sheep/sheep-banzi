#include <bits/stdc++.h>
using namespace std;
#define int long long

// Crystalfly三状态树DP：树上抓蝴蝶，邻点第一次被惊动后t≤3秒末消失。f是不计当前点收益的最优，g=f+a，h表示抓当前点后立刻返回的收益。
// O(n)时间/O(n)空间。
struct Crystalfly {
    int n;
    vector<vector<int>> e;
    vector<int> a, t, f, g, h;
    Crystalfly(int n = 0) {
        init(n);
    }
    void init(int n_) {
        n = n_;
        e.assign(n + 1, {});
        a.assign(n + 1, 0);
        t = a;
        f = a;
        g = a;
        h = a;
    }
    void add_edge(int u, int v) {
        e[u].push_back(v);
        e[v].push_back(u);
    }
    void dfs(int u, int fa) {
        int sum = 0, best = 0;
        pair<int, int> mx1 = {-1, 0}, mx2 = {-1, 0};
        for (int v : e[u])
            if (v != fa) {
                dfs(v, u);
                sum += f[v];
                best = max(best, a[v]);
                if (t[v] == 3) {
                    pair<int, int> z = {a[v], v};
                    if (z > mx1) {
                        mx2 = mx1;
                        mx1 = z;
                    } else if (z > mx2)
                        mx2 = z;
                }
            }
        h[u] = a[u] + sum;
        f[u] = sum + best;
        for (int v : e[u])
            if (v != fa) {
                int other = (mx1.second == v ? mx2.first : mx1.first);
                if (other >= 0)
                    f[u] = max(f[u], sum + h[v] - f[v] + other);
            }
        g[u] = f[u] + a[u];
    }
    int run(int root = 1) {
        dfs(root, 0);
        return g[root];
    }
};

void solve() {
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        Crystalfly c(n);
        for (int u = 1; u <= n; u++)
            cin >> c.a[u];
        for (int u = 1; u <= n; u++)
            cin >> c.t[u];
        for (int i = 1; i < n; i++) {
            int u, v;
            cin >> u >> v;
            c.add_edge(u, v);
        }
        cout << c.run() << '\n';
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

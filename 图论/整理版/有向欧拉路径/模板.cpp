#include <bits/stdc++.h>
using namespace std;
#define int long long

// 有向欧拉路径：Hierholzer递归删边与逆序；验证度条件和全边覆盖。
// 不排序O(n+m)，字典序排序O(m log m)，空间O(n+m)。
struct Euler {
    int n, m;
    vector<vector<int>> adj;
    vector<int> in, out, path;
    void init(int n_) {
        n = n_;
        m = 0;
        adj.assign(n + 1, {});
        in.assign(n + 1, 0);
        out = in;
        path.clear();
    }
    void addedge(int u, int v) {
        adj[u].push_back(v);
        out[u]++;
        in[v]++;
        m++;
    }
    void dfs(int u) {
        while (!adj[u].empty()) {
            int v = adj[u].back();
            adj[u].pop_back();
            dfs(v);
        }
        path.push_back(u);
    }
    bool run(bool lex = true) {
        int st = 0, en = 0;
        for (int u = 1; u <= n; u++) {
            int d = out[u] - in[u];
            if (d == 1) {
                if (st)
                    return false;
                st = u;
            } else if (d == -1) {
                if (en)
                    return false;
                en = u;
            } else if (d)
                return false;
        }
        if (bool(st) != bool(en))
            return false;
        if (!st)
            for (int u = 1; u <= n; u++)
                if (out[u]) {
                    st = u;
                    break;
                }
        if (!st)
            st = 1;
        if (lex)
            for (int u = 1; u <= n; u++)
                sort(adj[u].begin(), adj[u].end(), greater<int>());
        path.clear();
        dfs(st);
        reverse(path.begin(), path.end());
        return (int)path.size() == m + 1;
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    Euler g;
    g.init(n);
    while (m--) {
        int u, v;
        cin >> u >> v;
        g.addedge(u, v);
    }
    if (!g.run()) {
        cout << "No\n";
        return;
    }
    for (int u : g.path)
        cout << u << ' ';
    cout << '\n';
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

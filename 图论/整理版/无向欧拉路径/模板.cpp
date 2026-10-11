#include <bits/stdc++.h>
using namespace std;
#define int long long

// 无向欧拉路径：唯一边号标记、当前弧DFS，返回字典序最小无向欧拉路径。
// O(m log m+n)时间、O(n+m)空间。
struct Euler {
    struct edge {
        int v, id;
    };
    int n, m;
    vector<vector<edge>> adj;
    vector<int> deg, cur, vis, path;
    void init(int n_) {
        n = n_;
        m = 0;
        adj.assign(n + 1, {});
        deg.assign(n + 1, 0);
        cur = deg;
        vis.clear();
        path.clear();
    }
    void addedge(int u, int v) {
        adj[u].push_back({v, m});
        adj[v].push_back({u, m});
        deg[u]++;
        deg[v]++;
        vis.push_back(0);
        m++;
    }
    void dfs(int u) {
        for (int &i = cur[u]; i < (int)adj[u].size();) {
            auto [v, id] = adj[u][i++];
            if (vis[id])
                continue;
            vis[id] = 1;
            dfs(v);
        }
        path.push_back(u);
    }
    bool run() {
        int st = 0, odd = 0;
        for (int u = 1; u <= n; u++)
            if (deg[u] % 2) {
                odd++;
                if (!st)
                    st = u;
            }
        if (odd != 0 && odd != 2)
            return false;
        if (!st)
            for (int u = 1; u <= n; u++)
                if (deg[u]) {
                    st = u;
                    break;
                }
        if (!st)
            st = 1;
        for (int u = 1; u <= n; u++)
            sort(adj[u].begin(), adj[u].end(),
                 [](edge a, edge b) { return a.v < b.v; });
        fill(cur.begin(), cur.end(), 0);
        fill(vis.begin(), vis.end(), 0);
        path.clear();
        dfs(st);
        reverse(path.begin(), path.end());
        return (int)path.size() == m + 1;
    }
};

void solve() {
    int m;
    cin >> m;
    Euler g;
    g.init(500);
    while (m--) {
        int u, v;
        cin >> u >> v;
        g.addedge(u, v);
    }
    g.run();
    for (int u : g.path)
        cout << u << '\n';
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

#include <bits/stdc++.h>
using namespace std;
#define int long long

// Prim最小生成树：堆优化Prim无向图最小生成树；负边也可用；返回连通性与权值和。
// O(m log m)堆操作上界，空间O(n+m)。
struct Prim {
    struct edge {
        int v, w;
    };
    int n;
    vector<vector<edge>> e;
    void init(int n_) {
        n = n_;
        e.assign(n + 1, {});
    }
    void addedge(int u, int v, int w) {
        e[u].push_back({v, w});
        e[v].push_back({u, w});
    }
    pair<bool, int> run(int s = 1) {
        vector<int> vis(n + 1);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>>
            q;
        q.push({0, s});
        int total = 0, count = 0;
        while (!q.empty()) {
            auto [w, u] = q.top();
            q.pop();
            if (vis[u])
                continue;
            vis[u] = 1;
            total += w;
            count++;
            for (auto [v, c] : e[u])
                if (!vis[v])
                    q.push({c, v});
        }
        return {count == n, total};
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    Prim g;
    g.init(n);
    while (m--) {
        int u, v, w;
        cin >> u >> v >> w;
        g.addedge(u, v, w);
    }
    auto [ok, ans] = g.run();
    if (ok)
        cout << ans << '\n';
    else
        cout << "orz\n";
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

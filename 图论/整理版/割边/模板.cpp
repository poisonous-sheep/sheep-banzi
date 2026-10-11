#include <bits/stdc++.h>
using namespace std;
#define int long long

// 割边：无向图桥检测，按唯一边号跳过父边；支持重边和自环。
// O(n+m)时间与空间。
struct LowLink {
    int n, idx, cnt;
    vector<vector<pair<int, int>>> e;
    vector<pair<int, int>> edges;
    vector<int> dfn, low, sz, cut, bridge, bel;
    vector<vector<int>> parts, bcc;
    void init(int n_) {
        n = n_;
        idx = cnt = 0;
        e.assign(n + 1, {});
        edges.clear();
        dfn.assign(n + 1, 0);
        low = dfn;
        sz = dfn;
        cut = dfn;
        bel = dfn;
        parts.assign(n + 1, {});
        bridge.clear();
        bcc.clear();
    }
    void addedge(int u, int v) {
        int id = edges.size();
        edges.push_back({u, v});
        bridge.push_back(0);
        e[u].push_back({v, id});
        e[v].push_back({u, id});
    }
    void dfs(int u, int id) {
        dfn[u] = low[u] = ++idx;
        sz[u] = 1;
        int ch = 0;
        for (auto [v, id2] : e[u]) {
            if (id2 == id)
                continue;
            if (!dfn[v]) {
                ch++;
                dfs(v, id2);
                sz[u] += sz[v];
                low[u] = min(low[u], low[v]);
                if (low[v] > dfn[u])
                    bridge[id2] = 1;
                if (low[v] >= dfn[u]) {
                    parts[u].push_back(sz[v]);
                    if (id != -1)
                        cut[u] = 1;
                }
            } else
                low[u] = min(low[u], dfn[v]);
        }
        if (id == -1 && ch >= 2)
            cut[u] = 1;
    }
    void paint(int u) {
        bel[u] = cnt;
        bcc.back().push_back(u);
        for (auto [v, id] : e[u])
            if (!bridge[id] && !bel[v])
                paint(v);
    }
    void run() {
        for (int u = 1; u <= n; u++)
            if (!dfn[u])
                dfs(u, -1);
        for (int u = 1; u <= n; u++)
            if (!bel[u]) {
                cnt++;
                bcc.push_back({});
                paint(u);
            }
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    LowLink g;
    g.init(n);
    while (m--) {
        int u, v;
        cin >> u >> v;
        g.addedge(u, v);
    }
    g.run();
    vector<pair<int, int>> ans;
    for (int i = 0; i < (int)g.edges.size(); i++)
        if (g.bridge[i]) {
            auto [u, v] = g.edges[i];
            if (u > v)
                swap(u, v);
            ans.push_back({u, v});
        }
    sort(ans.begin(), ans.end());
    for (auto [u, v] : ans)
        cout << u << ' ' << v << '\n';
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

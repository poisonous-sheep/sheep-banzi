#include <bits/stdc++.h>
using namespace std;
#define int long long

// 最小费用最大流：逐次最短增广；费用势使残量边非负，用Dijkstra取最便宜增广路，支持无负环的负费用初始网络。
// 初始非负费用免预处理；有负费用时O(VE)建势，之后O(A*E log V)，A为增广次数；O(V+E)空间。
struct MinCostFlow {
    static constexpr int INF = 4000000000000000000LL;
    struct edge {
        int v, f, c;
    };
    int n;
    vector<edge> e;
    vector<vector<int>> g;
    vector<int> h, dis, pre;
    MinCostFlow(int n = 0) {
        init(n);
    }
    void init(int n_) {
        n = n_;
        e.clear();
        g.assign(n + 1, {});
        h.assign(n + 1, 0);
        dis = pre = h;
    }
    void add_edge(int u, int v, int f, int c) {
        int id = e.size();
        g[u].push_back(id);
        g[v].push_back(id ^ 1);
        e.push_back({v, f, c});
        e.push_back({u, 0, -c});
    }
    pair<int, int> run(int s, int t, int limit = INF) {
        assert(s != t);
        // 零势若已可行，无需Bellman-Ford；负费用时先建立全局可行势。
        fill(h.begin(), h.end(), 0);
        bool negative = false;
        for (auto z : e)
            if (z.f > 0 && z.c < 0)
                negative = true;
        if (negative)
            for (int k = 1; k <= n; k++) {
                bool changed = false;
                for (int u = 1; u <= n; u++)
                    for (int id : g[u]) {
                        auto z = e[id];
                        if (z.f > 0 && h[z.v] > h[u] + z.c)
                            h[z.v] = h[u] + z.c, changed = true;
                    }
                if (!changed)
                    break;
                assert(k < n);
            }
        int flow = 0, cost = 0;
        while (flow < limit) {
            fill(dis.begin(), dis.end(), INF);
            dis[s] = 0;
            priority_queue<pair<int, int>, vector<pair<int, int>>,
                           greater<pair<int, int>>>
                q;
            q.push({0, s});
            while (!q.empty()) {
                auto [d, u] = q.top();
                q.pop();
                if (d != dis[u])
                    continue;
                for (int id : g[u]) {
                    auto z = e[id];
                    if (z.f > 0 && dis[z.v] > d + z.c + h[u] - h[z.v]) {
                        dis[z.v] = d + z.c + h[u] - h[z.v];
                        pre[z.v] = id;
                        q.push({dis[z.v], z.v});
                    }
                }
            }
            if (dis[t] == INF)
                break;
            for (int u = 1; u <= n; u++)
                if (dis[u] < INF)
                    h[u] += dis[u];
            int f = limit - flow;
            for (int v = t; v != s; v = e[pre[v] ^ 1].v)
                f = min(f, e[pre[v]].f);
            for (int v = t; v != s; v = e[pre[v] ^ 1].v) {
                int id = pre[v];
                e[id].f -= f;
                e[id ^ 1].f += f;
                cost += f * e[id].c;
            }
            flow += f;
        }
        return {flow, cost};
    }
};

void solve() {
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    MinCostFlow g(n);
    while (m--) {
        int u, v, w, c;
        cin >> u >> v >> w >> c;
        g.add_edge(u, v, w, c);
    }
    auto [f, c] = g.run(s, t);
    cout << f << ' ' << c << '\n';
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

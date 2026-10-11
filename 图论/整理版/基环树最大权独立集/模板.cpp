#include <bits/stdc++.h>
using namespace std;
#define int long long

// 基环树最大权独立集：每个函数图分量一个环；外挂树选/不选DP后，环枚举首点选择并检查首尾冲突。
// O(n)时间与空间。
struct FunctionalGraph {
    int n;
    vector<int> p, w, val;
    vector<int32_t> head, nxt;
    vector<char> vis, on;
    vector<vector<int>> cycles;
    FunctionalGraph(int n = 0) {
        init(n);
    }
    void init(int n_) {
        n = n_;
        p.assign(n + 1, 0);
        w = val = p;
        head.assign(n + 1, -1);
        nxt = head;
        vis.assign(n + 1, 0);
        on = vis;
        cycles.clear();
    }
    void build() {
        fill(head.begin(), head.end(), -1);
        fill(vis.begin(), vis.end(), 0);
        fill(on.begin(), on.end(), 0);
        cycles.clear();
        for (int u = 1; u <= n; u++) {
            assert(1 <= p[u] && p[u] <= n);
            nxt[u] = head[p[u]];
            head[p[u]] = u;
        }
        for (int i = 1; i <= n; i++)
            if (!vis[i]) {
                int u = i;
                while (!vis[u])
                    vis[u] = 1, u = p[u];
                if (vis[u] == 1) {
                    vector<int> c;
                    int v = u;
                    do {
                        c.push_back(v);
                        on[v] = 1;
                        v = p[v];
                    } while (v != u);
                    cycles.push_back(c);
                }
                u = i;
                while (vis[u] == 1)
                    vis[u] = 2, u = p[u];
            }
    }
    void orient(const vector<array<int, 3>> &edges) {
        vector<vector<array<int, 3>>> g(n + 1);
        vector<int> deg(n + 1);
        int eid = 0;
        for (auto [u, v, c] : edges) {
            g[u].push_back({v, c, eid});
            g[v].push_back({u, c, eid++});
            deg[u]++;
            deg[v]++;
        }
        queue<int> q;
        for (int u = 1; u <= n; u++)
            if (deg[u] == 1)
                q.push(u);
        vector<char> removed(n + 1);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            removed[u] = 1;
            for (auto [v, c, id] : g[u])
                if (!removed[v]) {
                    p[u] = v;
                    w[u] = c;
                    if (--deg[v] == 1)
                        q.push(v);
                    break;
                }
        }
        vector<char> used(n + 1);
        for (int i = 1; i <= n; i++)
            if (!removed[i] && !used[i]) {
                int u = i, prev = -1;
                do {
                    used[u] = 1;
                    array<int, 3> z = {0, 0, -1};
                    for (auto [v, c, id] : g[u])
                        if (!removed[v] && id != prev) {
                            z = {v, c, id};
                            break;
                        }
                    assert(z[0]);
                    p[u] = z[0];
                    w[u] = z[1];
                    prev = z[2];
                    u = z[0];
                } while (u != i);
            }
        build();
    }
};

struct Knight : FunctionalGraph {
    static constexpr int INF = 4000000000000000000LL;
    vector<array<int, 2>> dp;
    Knight(int n = 0) : FunctionalGraph(n) {}
    void dfs(int u) {
        dp[u] = {0, val[u]};
        for (int v = head[u]; v != -1; v = nxt[v])
            if (!on[v]) {
                dfs(v);
                dp[u][0] += max(dp[v][0], dp[v][1]);
                dp[u][1] += dp[v][0];
            }
    }
    int run() {
        build();
        dp.assign(n + 1, {0, 0});
        int ans = 0;
        for (auto c : cycles) {
            for (int u : c)
                dfs(u);
            if (c.size() == 1) {
                ans += dp[c[0]][0];
                continue;
            }
            int best = -INF;
            for (int first = 0; first < 2; first++) {
                int f = first ? -INF : dp[c[0]][0], g = first ? dp[c[0]][1] : -INF;
                for (int i = 1; i < (int)c.size(); i++) {
                    int u = c[i];
                    int nf = max(f, g) + dp[u][0], ng = f == -INF ? -INF : f + dp[u][1];
                    f = nf;
                    g = ng;
                }
                best = max(best, first ? f : max(f, g));
            }
            ans += best;
        }
        return ans;
    }
};

void solve() {
    int n;
    cin >> n;
    Knight t(n);
    for (int u = 1; u <= n; u++)
        cin >> t.val[u] >> t.p[u];
    cout << t.run() << '\n';
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

#include <bits/stdc++.h>
using namespace std;
#define int long long

// 树上距离分层计数：用深度层节点数合并统计；原等距点集按中心各分支选点，固定距离数对用子树深度卷积。
// equidistant O(n²k)时间/O(nk)空间，适用n<=100；pairs O(nK)时间/空间。
struct TreeDistanceDP {
    int n, mod = 1000000007;
    vector<vector<int>> g;
    TreeDistanceDP(int n = 0) {
        init(n);
    }
    void init(int n_) {
        n = n_;
        g.assign(n + 1, {});
    }
    void add_edge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }
    void dfs(int u, int p, int d, vector<int> &cnt) {
        if (d >= (int)cnt.size())
            return;
        cnt[d]++;
        for (int v : g[u])
            if (v != p)
                dfs(v, u, d + 1, cnt);
    }
    int equidistant(int k) {
        if (k == 1)
            return n;
        if (k == 2)
            return n * (n - 1) / 2 % mod;
        int ans = 0;
        for (int u = 1; u <= n; u++) {
            vector<vector<int>> dp(n + 1, vector<int>(k + 1));
            for (auto &z : dp)
                z[0] = 1;
            for (int v : g[u]) {
                vector<int> cnt(n + 1);
                dfs(v, u, 1, cnt);
                for (int d = 1; d <= n; d++)
                    if (cnt[d])
                        for (int j = k; j >= 1; j--)
                            dp[d][j] = (dp[d][j] + dp[d][j - 1] * cnt[d]) % mod;
            }
            for (int d = 1; d <= n; d++)
                ans = (ans + dp[d][k]) % mod;
        }
        return ans;
    }
    int pairs(int K) {
        vector<vector<int32_t>> f(n + 1, vector<int32_t>(K + 1));
        int ans = 0;
        function<void(int, int)> work = [&](int u, int p) {
            f[u][0] = 1;
            for (int v : g[u])
                if (v != p) {
                    work(v, u);
                    for (int d = 0; d < K; d++)
                        ans += (int)f[u][d] * f[v][K - d - 1];
                    for (int d = 1; d <= K; d++)
                        f[u][d] += f[v][d - 1];
                }
        };
        work(1, 0);
        return ans;
    }
};

void solve() {
    int T;
    cin >> T;
    while (T--) {
        int n, k;
        cin >> n >> k;
        TreeDistanceDP t(n);
        for (int i = 1; i < n; i++) {
            int u, v;
            cin >> u >> v;
            t.add_edge(u, v);
        }
        cout << t.equidistant(k) << '\n';
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

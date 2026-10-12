// CF1551F https://codeforces.com/contest/1551/problem/F
#include <bits/stdc++.h>
using namespace std;
#define int long long

int n, mod = 1000000007;
vector<vector<int>> g;

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

void init_model(int n = 0) {
    init(n);
}

void solve() {
    int T;
    cin >> T;
    while (T--) {
        int n, k;
        cin >> n >> k;
        ::init_model(n);
        for (int i = 1; i < n; i++) {
            int u, v;
            cin >> u >> v;
            ::add_edge(u, v);
        }
        cout << ::equidistant(k) << '\n';
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

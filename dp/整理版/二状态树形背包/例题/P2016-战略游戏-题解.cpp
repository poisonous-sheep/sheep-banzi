// P2016 https://www.luogu.com.cn/problem/P2016
#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve() {
    int n;
    cin >> n;
    vector<vector<int>> e(n);
    for (int i = 0; i < n; i++) {
        int u, k;
        cin >> u >> k;
        while (k--) {
            int v;
            cin >> v;
            e[u].push_back(v);
            e[v].push_back(u);
        }
    }
    vector<array<int, 2>> dp(n);
    function<void(int, int)> dfs = [&](int u, int fa) {
        dp[u] = {0, 1};
        for (int v : e[u])
            if (v != fa) {
                dfs(v, u);
                dp[u][0] += dp[v][1];
                dp[u][1] += min(dp[v][0], dp[v][1]);
            }
    };
    dfs(0, -1);
    cout << min(dp[0][0], dp[0][1]) << '\n';
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

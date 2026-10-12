// ABC361E https://atcoder.jp/contests/abc361/tasks/abc361_e
#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve() {
    int n, sum = 0, diameter = 0;
    cin >> n;
    vector<vector<pair<int, int>>> e(n + 1);
    vector<int> f(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        e[u].push_back({v, w});
        e[v].push_back({u, w});
        sum += w;
    }
    function<void(int, int)> dfs = [&](int u, int fa) {
        int mx1 = 0, mx2 = 0;
        for (auto [v, w] : e[u])
            if (v != fa) {
                dfs(v, u);
                int z = f[v] + w;
                if (z >= mx1) {
                    mx2 = mx1;
                    mx1 = z;
                } else
                    mx2 = max(mx2, z);
            }
        f[u] = mx1;
        diameter = max(diameter, mx1 + mx2);
    };
    dfs(1, 0);
    cout << 2 * sum - diameter << '\n';
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

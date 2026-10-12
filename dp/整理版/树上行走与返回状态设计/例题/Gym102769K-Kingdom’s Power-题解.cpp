// Gym102769K https://codeforces.com/gym/102769/problem/K
#include <bits/stdc++.h>
using namespace std;
#define int long long

int n;
vector<int> fa, dep;
vector<array<int, 2>> dp;

void init(int n_) {
    n = n_;
    fa.assign(n + 1, 0);
    dep = fa;
    dp.assign(n + 1, {0, 0});
}
int run() {
    for (int u = 1; u <= n; u++) {
        if (u > 1) {
            assert(1 <= fa[u] && fa[u] < u);
            dep[u] = dep[fa[u]] + 1;
        }
        dp[u] = {0, dep[u]};
    }
    for (int v = n; v >= 2; v--) {
        int u = fa[v];
        dp[u][1] =
            min({dp[u][1] + dp[v][1], dp[u][1] + dp[v][0] + 2, dp[u][0] + dp[v][1]});
        dp[u][0] += dp[v][0] + 2;
    }
    return min(dp[1][0], dp[1][1]);
}

void init_model(int n = 0) {
    init(n);
}

void solve() {
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        int n;
        cin >> n;
        ::init_model(n);
        for (int u = 2; u <= n; u++)
            cin >> ::fa[u];
        cout << "Case #" << tc << ": " << ::run() << '\n';
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

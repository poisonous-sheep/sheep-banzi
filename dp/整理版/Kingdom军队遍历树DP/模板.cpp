#include <bits/stdc++.h>
using namespace std;
#define int long long

// Kingdom军队遍历树DP：根可派任意多支军队，每次只能移动一支一步，求访问全树的最小总步数。保留原稿按父编号倒序合并的线性算法。
// O(n)时间/O(n)空间。
struct KingdomPower {
    int n;
    vector<int> fa, dep;
    vector<array<int, 2>> dp;
    KingdomPower(int n = 0) {
        init(n);
    }
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
            dp[u][1] = min(
                {dp[u][1] + dp[v][1], dp[u][1] + dp[v][0] + 2, dp[u][0] + dp[v][1]});
            dp[u][0] += dp[v][0] + 2;
        }
        return min(dp[1][0], dp[1][1]);
    }
};

void solve() {
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        int n;
        cin >> n;
        KingdomPower t(n);
        for (int u = 2; u <= n; u++)
            cin >> t.fa[u];
        cout << "Case #" << tc << ": " << t.run() << '\n';
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

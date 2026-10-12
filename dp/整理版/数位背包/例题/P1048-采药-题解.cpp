// P1048 https://www.luogu.com.cn/problem/P1048
#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve() {
    int T, M;
    cin >> T >> M;
    vector<int> dp(T + 1);
    while (M--) {
        int w, v;
        cin >> w >> v;
        for (int j = T; j >= w; j--)
            dp[j] = max(dp[j], dp[j - w] + v);
    }
    cout << dp[T] << '\n';
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

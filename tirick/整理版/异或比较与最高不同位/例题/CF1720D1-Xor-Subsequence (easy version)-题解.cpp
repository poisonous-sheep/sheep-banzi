// CF1720D1 https://codeforces.com/problemset/problem/1720/D1
#include <bits/stdc++.h>
using namespace std;
#define int long long

int subsequence(const vector<int> &a, int B = 8) {
    int n = a.size(), ans = 0, lim = 1LL << B;
    vector<int> dp(n, 1);
    for (int i = 0; i < n; i++) {
        assert(0 <= a[i] && a[i] < lim);
        for (int j = max(0LL, i - lim + 1); j < i; j++)
            if ((a[j] ^ i) < (a[i] ^ j))
                dp[i] = max(dp[i], dp[j] + 1);
        ans = max(ans, dp[i]);
    }
    return ans;
}

void init_model() {
}

void solve() {
    int T;
    cin >> T;
    ::init_model();
    while (T--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int &x : a)
            cin >> x;
        cout << ::subsequence(a) << '\n';
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

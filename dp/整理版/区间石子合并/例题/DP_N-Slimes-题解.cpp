// DP_N https://atcoder.jp/contests/dp/tasks/dp_n
#include <bits/stdc++.h>
using namespace std;
#define int long long

static constexpr int INF = 4000000000000000000LL;
int binary(const vector<int> &a, bool circle = false, bool maximum = false) {
    int n = a.size(), N = circle ? 2 * n : n;
    vector<int> s(N + 1);
    for (int i = 1; i <= N; i++)
        s[i] = s[i - 1] + a[(i - 1) % n];
    vector<vector<int>> dp(N + 2, vector<int>(N + 2));
    for (int len = 2; len <= n; len++)
        for (int l = 1; l + len - 1 <= N; l++) {
            int r = l + len - 1;
            dp[l][r] = maximum ? -INF : INF;
            for (int k = l; k < r; k++) {
                int val = dp[l][k] + dp[k + 1][r] + s[r] - s[l - 1];
                if (maximum)
                    dp[l][r] = max(dp[l][r], val);
                else
                    dp[l][r] = min(dp[l][r], val);
            }
        }
    int ans = maximum ? -INF : INF;
    for (int l = 1; l <= (circle ? n : 1); l++)
        if (maximum)
            ans = max(ans, dp[l][l + n - 1]);
        else
            ans = min(ans, dp[l][l + n - 1]);
    return ans;
}
int arity(const vector<int> &a, int L, int R) {
    assert(2 <= L && L <= R);
    int n = a.size();
    vector<int> s(n + 1);
    for (int i = 1; i <= n; i++)
        s[i] = s[i - 1] + a[i - 1];
    vector<vector<vector<int>>> dp(n + 2,
                                   vector<vector<int>>(n + 2, vector<int>(n + 1, INF)));
    for (int i = 1; i <= n; i++)
        dp[i][i][1] = 0;
    for (int len = 2; len <= n; len++)
        for (int l = 1; l + len - 1 <= n; l++) {
            int r = l + len - 1;
            for (int k = 2; k <= min(R, len); k++)
                for (int mid = l; mid < r; mid++)
                    if (dp[l][mid][1] < INF && dp[mid + 1][r][k - 1] < INF)
                        dp[l][r][k] =
                            min(dp[l][r][k], dp[l][mid][1] + dp[mid + 1][r][k - 1]);
            for (int k = L; k <= min(R, len); k++)
                if (dp[l][r][k] < INF)
                    dp[l][r][1] = min(dp[l][r][1], dp[l][r][k] + s[r] - s[l - 1]);
        }
    return n ? dp[1][n][1] : 0;
}

void init_model() {
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int &x : a)
        cin >> x;
    ::init_model();
    cout << ::binary(a) << '\n';
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

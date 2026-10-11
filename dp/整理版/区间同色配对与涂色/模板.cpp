#include <bits/stdc++.h>
using namespace std;
#define int long long

// 区间同色配对与涂色：压缩相邻同色后，配对相同端点节省操作；收录原Cities最大节省状态与清空/涂色的次数接口。
// O(n³)最坏时间、O(n²)空间；每色最多f次时O(fn²)。
struct SequencePaint {
    vector<int> a, nxt;
    vector<vector<int>> dp;
    void init(const vector<int> &v) {
        a = {0};
        for (int x : v)
            if (a.size() == 1 || a.back() != x)
                a.push_back(x);
        int n = a.size() - 1;
        nxt.assign(n + 2, n + 1);
        map<int, int> pos;
        for (int i = n; i >= 1; i--) {
            if (pos.count(a[i]))
                nxt[i] = pos[a[i]];
            pos[a[i]] = i;
        }
        dp.assign(n + 2, vector<int>(n + 2));
        for (int l = n; l >= 1; l--)
            for (int r = l; r <= n; r++) {
                dp[l][r] = dp[l + 1][r];
                for (int x = nxt[l]; x <= r; x = nxt[x])
                    dp[l][r] = max(dp[l][r], dp[l + 1][x - 1] + dp[x][r] + 1);
            }
    }
    int clear_min() {
        int n = a.size() - 1;
        return n - dp[1][n];
    }
    int uniform_min() {
        return max(0LL, clear_min() - 1);
    }
};

void solve() {
    int n;
    string s;
    cin >> n >> s;
    SequencePaint t;
    t.init(vector<int>(s.begin(), s.end()));
    cout << t.clear_min() << '\n';
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

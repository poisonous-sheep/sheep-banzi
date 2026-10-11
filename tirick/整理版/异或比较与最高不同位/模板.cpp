#include <bits/stdc++.h>
using namespace std;
#define int long long

// 异或比较与最高不同位：非负数满足|x-y|≤x xor y≤x+y；异或比较由最高不同位决定，低位值域可截断DP转移。
// subsequence O(n*2^B)时间/O(n)空间；max_xor O(log r)时间/O(1)空间。
struct XorCompare {
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
    int max_xor(int l, int r) {
        assert(0 <= l && l <= r);
        int x = l ^ r, ans = 0;
        while (x) {
            ans = (ans << 1) | 1;
            x >>= 1;
        }
        return ans;
    }
};

void solve() {
    int T;
    cin >> T;
    XorCompare t;
    while (T--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int &x : a)
            cin >> x;
        cout << t.subsequence(a) << '\n';
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

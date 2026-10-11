#include <bits/stdc++.h>
using namespace std;
#define int long long

// 二进制位贡献与Popcount计数：位独立贡献的乘法原理：原Meaningless Sequence加权和、按掩码统计1位次数、按popcount分类。
// weighted O(L)时间/空间；masked O(log n)时间/O(1)空间；distribution O(log² n)时间/空间。
struct PopcountDP {
    int mod;
    PopcountDP(int mod = 1000000007) : mod(mod) {}
    int weighted(string s, int c) {
        int n = s.size();
        c %= mod;
        vector<int> pw(n + 1, 1);
        for (int i = 1; i <= n; i++)
            pw[i] = pw[i - 1] * (c + 1) % mod;
        int pre = 1, ans = 0;
        for (int i = 0; i < n; i++)
            if (s[i] == '1') {
                ans = (ans + pre * pw[n - i - 1]) % mod;
                pre = pre * c % mod;
            }
        return (ans + pre) % mod;
    }
    int masked(int n, int mask) {
        int ans = 0;
        for (int b = 0; b <= 60; b++)
            if ((mask >> b) & 1) {
                __int128 bit = (__int128)1 << b, period = bit * 2,
                         len = (__int128)n + 1;
                __int128 c =
                    (len / period) * bit + max((__int128)0, len % period - bit);
                ans = (ans + c % mod) % mod;
            }
        return ans;
    }
    vector<int> distribution(int n) {
        string s;
        do {
            s.push_back('0' + (n & 1));
            n >>= 1;
        } while (n);
        reverse(s.begin(), s.end());
        int L = s.size();
        vector<vector<int>> C(L + 1, vector<int>(L + 1));
        C[0][0] = 1;
        for (int i = 1; i <= L; i++) {
            C[i][0] = C[i][i] = 1;
            for (int j = 1; j < i; j++)
                C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
        }
        vector<int> ans(L + 1);
        int ones = 0;
        for (int i = 0; i < L; i++)
            if (s[i] == '1') {
                for (int k = 0; k <= L - i - 1; k++)
                    ans[ones + k] += C[L - i - 1][k];
                ones++;
            }
        ans[ones]++;
        return ans;
    }
    int powmod(int a, int b) {
        int r = 1;
        while (b) {
            if (b & 1)
                r = (__int128)r * a % mod;
            a = (__int128)a * a % mod;
            b >>= 1;
        }
        return r;
    }
};

void solve() {
    string N;
    int c;
    cin >> N >> c;
    PopcountDP t;
    cout << t.weighted(N, c) << '\n';
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

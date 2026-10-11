#include <bits/stdc++.h>
using namespace std;
#define int long long

// 括号计数与无歧义区间DP：普通通配括号用余额状态；超级括号用首个完整括号块唯一分解，避免拼接计数重复。
// normal O(n²)时间/O(n)空间；super O(n³)时间/O(n²)空间。
struct BracketDP {
    int mod;
    BracketDP(int mod = 1000000007) : mod(mod) {}
    int normal(string s) {
        int n = s.size();
        vector<int> f(n + 2), g(n + 2);
        f[0] = 1;
        for (char c : s) {
            fill(g.begin(), g.end(), 0);
            for (int d = 0; d <= n; d++)
                if (f[d]) {
                    if (c == '(' || c == '?')
                        g[d + 1] = (g[d + 1] + f[d]) % mod;
                    if (d && (c == ')' || c == '?'))
                        g[d - 1] = (g[d - 1] + f[d]) % mod;
                }
            f.swap(g);
        }
        return f[0];
    }
    int super(string s, int k) {
        int n = s.size();
        s = " " + s;
        vector<vector<int>> f(n + 2, vector<int>(n + 2)), wrap = f, left = f, right = f,
                                                          star = f;
        for (int l = 1; l <= n; l++)
            for (int r = l; r <= min(n, l + k - 1); r++) {
                if (s[r] != '*' && s[r] != '?')
                    break;
                star[l][r] = 1;
            }
        auto add = [&](int &x, int y) { x = (x + y) % mod; };
        for (int len = 1; len <= n; len++)
            for (int l = 1; l + len - 1 <= n; l++) {
                int r = l + len - 1;
                if (len >= 2 && (s[l] == '(' || s[l] == '?') &&
                    (s[r] == ')' || s[r] == '?')) {
                    int val = len == 2 ? 1 : star[l + 1][r - 1];
                    if (len > 2) {
                        add(val, f[l + 1][r - 1]);
                        add(val, left[l + 1][r - 1]);
                        add(val, right[l + 1][r - 1]);
                    }
                    wrap[l][r] = val;
                }
                f[l][r] = wrap[l][r];
                for (int mid = l + 1; mid < r; mid++)
                    add(f[l][r],
                        wrap[l][mid] * (f[mid + 1][r] + left[mid + 1][r]) % mod);
                for (int mid = l; mid < r && mid - l + 1 <= k; mid++)
                    if (star[l][mid])
                        add(left[l][r], f[mid + 1][r]);
                for (int mid = r - 1; mid >= l && r - mid <= k; mid--)
                    if (star[mid + 1][r])
                        add(right[l][r], f[l][mid]);
            }
        return n ? f[1][n] : 0;
    }
};

void solve() {
    int n, k;
    string s;
    cin >> n >> k >> s;
    BracketDP t;
    cout << t.super(s, k) << '\n';
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

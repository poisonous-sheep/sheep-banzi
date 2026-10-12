// P7914 https://www.luogu.com.cn/problem/P7914
#include <bits/stdc++.h>
using namespace std;
#define int long long

int mod;

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
                add(f[l][r], wrap[l][mid] * (f[mid + 1][r] + left[mid + 1][r]) % mod);
            for (int mid = l; mid < r && mid - l + 1 <= k; mid++)
                if (star[l][mid])
                    add(left[l][r], f[mid + 1][r]);
            for (int mid = r - 1; mid >= l && r - mid <= k; mid--)
                if (star[mid + 1][r])
                    add(right[l][r], f[l][mid]);
        }
    return n ? f[1][n] : 0;
}

void init_model(int mod_ = 1000000007) {
    mod = mod_;
}

void solve() {
    int n, k;
    string s;
    cin >> n >> k >> s;
    ::init_model();
    cout << ::super(s, k) << '\n';
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

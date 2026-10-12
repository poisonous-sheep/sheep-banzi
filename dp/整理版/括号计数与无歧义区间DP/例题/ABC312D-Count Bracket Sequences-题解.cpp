// ABC312D https://atcoder.jp/contests/abc312/tasks/abc312_d
#include <bits/stdc++.h>
using namespace std;
#define int long long

int mod;

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

void init_model(int mod_ = 1000000007) {
    mod = mod_;
}

void solve() {
    string s;
    cin >> s;
    ::init_model(998244353);
    cout << ::normal(s) << '\n';
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

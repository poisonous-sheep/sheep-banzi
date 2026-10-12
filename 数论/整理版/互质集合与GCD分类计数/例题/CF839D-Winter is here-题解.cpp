// CF839D https://codeforces.com/contest/839/problem/D
#include <bits/stdc++.h>
using namespace std;
#define int long long

// 组合依赖：本册 莫比乌斯反演与线性筛 的 Mobius 定义。


int n, mod;
vector<int> cnt, pw, exact;
Mobius sieve;

void init(const vector<int> &a, int mod_ = 1000000007) {
    mod = mod_;
    n = a.empty() ? 0 : *max_element(a.begin(), a.end());
    sieve.init(n);
    vector<int> freq(n + 1);
    for (int x : a) {
        assert(x > 0);
        freq[x]++;
    }
    cnt.assign(n + 1, 0);
    for (int d = 1; d <= n; d++)
        for (int j = d; j <= n; j += d)
            cnt[d] += freq[j];
    pw.assign(a.size() + 1, 1);
    for (int i = 1; i < (int)pw.size(); i++)
        pw[i] = pw[i - 1] * 2 % mod;
}

int weighted() {
    exact.assign(n + 1, 0);
    int ans = 0;
    for (int d = n; d >= 1; d--) {
        int c = cnt[d];
        exact[d] = c ? c * pw[c - 1] % mod : 0;
        for (int j = d + d; j <= n; j += d)
            exact[d] = (exact[d] - exact[j] + mod) % mod;
        if (d > 1)
            ans = (ans + d * exact[d]) % mod;
    }
    return ans;
}

void init_model(const vector<int> &a, int mod_ = 1000000007) {
    init(a, mod_);
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int &x : a)
        cin >> x;
    ::init_model(a);
    cout << ::weighted() << '\n';
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

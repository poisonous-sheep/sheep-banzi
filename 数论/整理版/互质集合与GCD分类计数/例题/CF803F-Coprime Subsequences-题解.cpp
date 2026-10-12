// CF803F https://codeforces.com/contest/803/problem/F
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
int qur() {
    int ans = 0;
    for (int d = 1; d <= n; d++)
        ans = (ans + sieve.mu[d] * (pw[cnt[d]] - 1)) % mod;
    return (ans + mod) % mod;
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
    cout << ::qur() << '\n';
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

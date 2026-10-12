// AGC038C https://atcoder.jp/contests/agc038/tasks/agc038_c
#include <bits/stdc++.h>
using namespace std;
#define int long long

int n, mod;
vector<int> h, pre, p, pr;

int norm(int x) {
    return (x % mod + mod) % mod;
}
int mul(int a, int b) {
    return (__int128)a * b % mod;
}

void init(int n_, int m) {
    n = n_;
    mod = m;
    assert(mod > 0);
    h.assign(n + 1, 0);
    pre = p = h;
    pr.clear();
    if (n)
        h[1] = 1 % mod;
    for (int i = 2; i <= n; i++) {
        if (!p[i])
            p[i] = i, pr.push_back(i), h[i] = norm(i * (1 - i));
        for (int x : pr) {
            if (x > n / i)
                break;
            p[i * x] = x;
            if (i % x == 0) {
                h[i * x] = mul(h[i], x);
                break;
            }
            h[i * x] = mul(h[i], norm(x * (1 - x)));
        }
    }
    for (int i = 1; i <= n; i++)
        pre[i] = (pre[i - 1] + h[i]) % mod;
}

int pairs(const vector<int> &a) {
    vector<int> s(n + 1), freq(n + 1);
    int diag = 0;
    for (int x : a) {
        assert(1 <= x && x <= n);
        freq[x]++;
        diag = (diag + x) % mod;
    }
    for (int d = 1; d <= n; d++)
        for (int x = d; x <= n; x += d)
            s[d] = (s[d] + mul(freq[x], x / d)) % mod;
    int ans = 0;
    for (int d = 1; d <= n; d++)
        ans = (ans + mul(h[d], mul(s[d], s[d]))) % mod;
    assert(mod & 1);
    return mul(norm(ans - diag), (mod + 1) / 2);
}

void init_model(int n = 0, int mod = 20101009) {
    init(n, mod);
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int &x : a)
        cin >> x;
    ::init_model(*max_element(a.begin(), a.end()), 998244353);
    cout << ::pairs(a) << '\n';
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

// P1829 https://www.luogu.com.cn/problem/P1829
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
int S(int x) {
    int a = x, b = x + 1;
    if (a % 2 == 0)
        a /= 2;
    else
        b /= 2;
    return mul(a % mod, b % mod);
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
int qur(int a, int b) {
    if (a > b)
        swap(a, b);
    assert(a <= n);
    int ans = 0;
    for (int l = 1, r; l <= a; l = r + 1) {
        int x = a / l, y = b / l;
        r = min(a / x, b / y);
        ans = (ans + mul(norm(pre[r] - pre[l - 1]), mul(S(x), S(y)))) % mod;
    }
    return ans;
}

void init_model(int n = 0, int mod = 20101009) {
    init(n, mod);
}

void solve() {
    int n, m;
    cin >> n >> m;
    ::init_model(min(n, m), 20101009);
    cout << ::qur(n, m) << '\n';
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

#include <bits/stdc++.h>
using namespace std;
#define int long long

// Lucas定理：大n、小素数p的组合数模p；保留逐p进制位乘binom。
// 预处理O(p)，单问O(log_p n)，空间O(p)。
struct Comb {
    int mod;
    vector<int> fac, fnv;
    int powmod(int a, int b) {
        int ans = 1 % mod;
        for (a %= mod; b; b >>= 1, a = (__int128)a * a % mod)
            if (b & 1)
                ans = (__int128)ans * a % mod;
        return ans;
    }
    void init(int n, int p = 1000000007) {
        assert(p > 1 && n < p);
        mod = p;
        fac.assign(n + 1, 1);
        fnv.assign(n + 1, 1);
        for (int i = 1; i <= n; i++)
            fac[i] = fac[i - 1] * i % mod;
        fnv[n] = powmod(fac[n], mod - 2);
        for (int i = n; i >= 1; i--)
            fnv[i - 1] = fnv[i] * i % mod;
    }
    int binom(int n, int m) {
        if (m < 0 || m > n)
            return 0;
        assert(n < (int)fac.size());
        return fac[n] * fnv[m] % mod * fnv[n - m] % mod;
    }
};

struct Lucas {
    int p;
    Comb c;
    void init(int p_) {
        p = p_;
        c.init(p - 1, p);
    }
    int binom(int n, int m) {
        if (m < 0 || m > n)
            return 0;
        int ans = 1;
        while (n || m) {
            ans = ans * c.binom(n % p, m % p) % p;
            n /= p;
            m /= p;
        }
        return ans;
    }
    int powmod(int a, int b) {
        return c.powmod(a, b);
    }
};

void solve() {
    int T;
    cin >> T;
    while (T--) {
        int n, m, p;
        cin >> n >> m >> p;
        Lucas c;
        c.init(p);
        cout << c.binom(n + m, n) << '\n';
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

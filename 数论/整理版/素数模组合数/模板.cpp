#include <bits/stdc++.h>
using namespace std;
#define int long long

// 素数模组合数：阶乘与逆阶乘计算组合数；p为素数，预处理范围n<p。
// 预处理O(n+log p)，每问O(1)，空间O(n)。
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

void solve() {
    int w, h;
    cin >> w >> h;
    Comb c;
    c.init(w + h - 2);
    cout << c.binom(w + h - 2, w - 1) << '\n';
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

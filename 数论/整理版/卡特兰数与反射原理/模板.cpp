#include <bits/stdc++.h>
using namespace std;
#define int long long

// 卡特兰数与反射原理：计数栈出入、合法括号与不越界格路径；精确递推与反射法的组合数差。
// exact O(n)时间/O(1)空间；ballot O(n+m)时间/空间。
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
struct Catalan {
    int exact(int n) {
        assert(0 <= n && n <= 35);
        __int128 c = 1;
        for (int i = 1; i <= n; i++)
            c = c * 2 * (2 * i - 1) / (i + 1);
        return c;
    }
    int ballot(int n, int m, int mod) {
        if (n < m)
            return 0;
        Comb t;
        t.init(n + m, mod);
        return (t.binom(n + m, m) - t.binom(n + m, m - 1) + mod) % mod;
    }
};

void solve() {
    int n;
    cin >> n;
    Catalan t;
    cout << t.exact(n) << '\n';
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

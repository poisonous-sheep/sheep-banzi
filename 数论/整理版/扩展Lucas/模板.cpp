#include <bits/stdc++.h>
using namespace std;
#define int long long

// 扩展Lucas：合数模组合数，按质数幂去除阶乘质因子后CRT；单质数幂<=2e6。
// 预处理O(sqrt M+Σp^e)，每问O(Σlog_p n*log(p^e))，空间O(Σp^e)。
struct Exgcd {
    int exgcd(int a, int b, int &x, int &y) {
        if (!b) {
            x = 1;
            y = 0;
            return a;
        }
        int g = exgcd(b, a % b, y, x);
        y -= a / b * x;
        return g;
    }
    int norm(int a, int m) {
        a %= m;
        return a < 0 ? a + m : a;
    }
    int inverse(int a, int m) {
        int x, y;
        int g = exgcd(norm(a, m), m, x, y);
        return g == 1 ? norm(x, m) : -1;
    }
    int linear(int a, int b, int m) {
        assert(m > 0);
        a = norm(a, m);
        b = norm(b, m);
        int x, y, g = exgcd(a, m, x, y);
        if (b % g)
            return -1;
        return norm((__int128)x * (b / g) % (m / g), m / g);
    }
};

struct ExLucas {
    struct node {
        int p, pe;
        vector<int> fac;
    };
    int mod;
    vector<node> parts;
    Exgcd ex;
    int powmod(int a, int b, int m) {
        int ans = 1 % m;
        for (a %= m; b; b >>= 1, a = (__int128)a * a % m)
            if (b & 1)
                ans = (__int128)ans * a % m;
        return ans;
    }
    void init(int m) {
        assert(m >= 1);
        mod = m;
        parts.clear();
        int q = m;
        for (int p = 2; p <= q / p; p++)
            if (q % p == 0) {
                int pe = 1;
                while (q % p == 0) {
                    q /= p;
                    pe *= p;
                }
                parts.push_back({p, pe, {}});
            }
        if (q > 1)
            parts.push_back({q, q, {}});
        for (auto &v : parts) {
            assert(v.pe <= 2000000);
            v.fac.assign(v.pe + 1, 1);
            for (int i = 1; i <= v.pe; i++)
                v.fac[i] = v.fac[i - 1] * (i % v.p ? i : 1) % v.pe;
        }
    }
    int valuation(int n, int p) {
        int ans = 0;
        while (n) {
            n /= p;
            ans += n;
        }
        return ans;
    }
    int fact(int n, const node &v) {
        if (!n)
            return 1;
        return powmod(v.fac[v.pe], n / v.pe, v.pe) * v.fac[n % v.pe] % v.pe *
               fact(n / v.p, v) % v.pe;
    }
    int binom(int n, int m) {
        if (m < 0 || m > n || mod == 1)
            return 0;
        int ans = 0;
        for (auto &v : parts) {
            int exp = valuation(n, v.p) - valuation(m, v.p) - valuation(n - m, v.p);
            int a = fact(n, v), b = fact(m, v) * fact(n - m, v) % v.pe;
            int val = a * ex.inverse(b, v.pe) % v.pe * powmod(v.p, exp, v.pe) % v.pe;
            int M = mod / v.pe;
            ans = (ans + (__int128)val * M * ex.inverse(M, v.pe)) % mod;
        }
        return ans;
    }
};

void solve() {
    int n, m, p;
    cin >> n >> m >> p;
    ExLucas c;
    c.init(p);
    cout << c.binom(n, m) << '\n';
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

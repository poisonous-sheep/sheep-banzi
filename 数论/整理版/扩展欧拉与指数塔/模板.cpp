#include <bits/stdc++.h>
using namespace std;
#define int long long

// 扩展欧拉与指数塔：固定2的无限幂塔，以及正整数数组区间幂塔模m；通过phi链与真实阈值判定。
// phi试除按链各层求和；缓存后每问按O(log m)级链深递归及截断幂比较，空间为链深。
struct PowerTower {
    vector<int> a;
    map<int, int> phi_cache;
    int phi(int m) {
        if (phi_cache.count(m))
            return phi_cache[m];
        int ans = m, q = m;
        for (int p = 2; p <= q / p; p++)
            if (q % p == 0) {
                ans = ans / p * (p - 1);
                while (q % p == 0)
                    q /= p;
            }
        if (q > 1)
            ans = ans / q * (q - 1);
        return phi_cache[m] = ans;
    }
    int powmod(int x, int e, int m) {
        int ans = 1 % m;
        for (x %= m; e; e >>= 1, x = (__int128)x * x % m)
            if (e & 1)
                ans = (__int128)ans * x % m;
        return ans;
    }
    int calc(int m) {
        if (m == 1)
            return 0;
        int p = phi(m);
        return powmod(2, calc(p) + p, m);
    }
    void init(const vector<int> &v) {
        a = v;
        for (int i = 1; i < (int)a.size(); i++)
            assert(a[i] >= 1);
    }
    // 返回min(真实幂塔,limit)，只用于阈值判断；避免用已取模指数判断大小。
    int cap(int l, int r, int limit) {
        if (limit <= 1)
            return limit;
        if (l == r)
            return min(a[l], limit);
        if (a[l] == 1)
            return 1;
        int need = 0;
        __int128 val = 1;
        while (val < limit) {
            val *= a[l];
            need++;
        }
        int e = cap(l + 1, r, need);
        val = 1;
        while (e-- && val < limit)
            val *= a[l];
        return val >= limit ? limit : (int)val;
    }
    int qur(int l, int r, int m) {
        if (m == 1)
            return 0;
        if (l == r)
            return a[l] % m;
        int p = phi(m);
        int e = qur(l + 1, r, p);
        if (cap(l + 1, r, p) >= p)
            e += p;
        return powmod(a[l], e, m);
    }
};

void solve() {
    int T;
    cin >> T;
    PowerTower tr;
    while (T--) {
        int p;
        cin >> p;
        cout << tr.calc(p) << '\n';
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

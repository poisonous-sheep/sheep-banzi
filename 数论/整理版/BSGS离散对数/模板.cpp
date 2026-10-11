#include <bits/stdc++.h>
using namespace std;
#define int long long

// BSGS离散对数：求a^x=b mod m的最小非负x；保留map大步小步思路，并扩展非互质约除。
// O(sqrt m log m)时间、O(sqrt m)空间。
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

struct BSGS {
    Exgcd ex;
    int powmod(int a, int b, int m) {
        int ans = 1 % m;
        for (a %= m; b; b >>= 1, a = (__int128)a * a % m)
            if (b & 1)
                ans = (__int128)ans * a % m;
        return ans;
    }
    int unit(int a, int b, int m) {
        if (m == 1)
            return 0;
        int t = sqrtl((long double)m) + 1;
        map<int, int> hs;
        int v = 1 % m;
        for (int j = 0; j < t; j++) {
            if (!hs.count(v))
                hs[v] = j;
            v = (__int128)v * a % m;
        }
        int factor = ex.inverse(powmod(a, t, m), m), cur = b;
        for (int q = 0; q <= t; q++) {
            if (hs.count(cur))
                return q * t + hs[cur];
            cur = (__int128)cur * factor % m;
        }
        return -1;
    }
    int solve(int a, int b, int m) {
        assert(m > 0);
        a = ex.norm(a, m);
        b = ex.norm(b, m);
        if (m == 1)
            return 0;
        int k = 1 % m, count = 0;
        for (int g = gcd(a, m); g > 1; g = gcd(a, m)) {
            if (b == k)
                return count;
            if (b % g)
                return -1;
            b /= g;
            m /= g;
            k = (__int128)k * (a / g) % m;
            count++;
        }
        int x = unit(a % m, (__int128)b * ex.inverse(k, m) % m, m);
        return x < 0 ? -1 : x + count;
    }
};

void solve() {
    int p, b, n;
    cin >> p >> b >> n;
    BSGS g;
    int ans = g.solve(b, n, p);
    if (ans < 0)
        cout << "no solution\n";
    else
        cout << ans << '\n';
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

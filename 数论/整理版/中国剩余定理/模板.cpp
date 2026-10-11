#include <bits/stdc++.h>
using namespace std;
#define int long long

// 中国剩余定理：逐式合并同余，兼容两两互质CRT与非互质扩展CRT。
// n条同余约O(n log M)时间，额外O(log M)递归空间。
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

struct CRT {
    Exgcd ex;
    int ans = 0, mod = 1;
    void init() {
        ans = 0;
        mod = 1;
    }
    bool merge(int r, int m) {
        assert(m > 0);
        r = ex.norm(r, m);
        int x, y, g = ex.exgcd(mod, m, x, y);
        int delta = r - ans;
        if (delta % g)
            return false;
        int q = m / g;
        int k = ex.norm((__int128)(delta / g) * x % q, q);
        __int128 nm = (__int128)mod * q;
        assert(nm <= LLONG_MAX);
        ans = ((__int128)ans + (__int128)mod * k) % nm;
        mod = nm;
        return true;
    }
};

void solve() {
    int n;
    cin >> n;
    CRT crt;
    while (n--) {
        int m, r;
        cin >> m >> r;
        crt.merge(r, m);
    }
    cout << crt.ans << '\n';
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

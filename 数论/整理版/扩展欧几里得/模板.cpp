#include <bits/stdc++.h>
using namespace std;
#define int long long

// 扩展欧几里得：求Bezout系数、模逆元与线性同余最小非负解；模数为正。
// O(log m)时间与递归空间。
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

void solve() {
    int a, b;
    cin >> a >> b;
    Exgcd ex;
    int x = ex.inverse(a, b);
    cout << (x == 0 ? b : x) << '\n';
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

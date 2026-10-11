#include <bits/stdc++.h>
using namespace std;
#define int long long

// 整除分块：相同floor(n/i)的连续区间合并；同时支持两个商不变的分块。
// 单商/双商分块O(sqrt n+sqrt m)，额外O(1)空间。
struct FloorBlock {
    template <class F> void run(int n, F calc) {
        for (int l = 1, r; l <= n; l = r + 1) {
            int q = n / l;
            r = n / q;
            calc(l, r, q);
        }
    }
    template <class F> void run(int n, int m, F calc) {
        for (int l = 1, r; l <= min(n, m); l = r + 1) {
            int a = n / l, b = m / l;
            r = min(n / a, m / b);
            calc(l, r, a, b);
        }
    }
    int count_divisors_sum(int n) {
        int ans = 0;
        run(n, [&](int l, int r, int q) { ans += (r - l + 1) * q; });
        return ans;
    }
    __int128 divisor_sum(int n) {
        __int128 ans = 0;
        if (n <= 0)
            return 0;
        run(n, [&](int l, int r, int q) {
            ans += (__int128)(l + r) * (r - l + 1) / 2 * q;
        });
        return ans;
    }
    void print(__int128 x) {
        if (x < 0) {
            cout << '-';
            x = -x;
        }
        if (x >= 10)
            print(x / 10);
        cout << char('0' + x % 10);
    }
};

void solve() {
    int n;
    cin >> n;
    FloorBlock f;
    cout << f.count_divisors_sum(n) << '\n';
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

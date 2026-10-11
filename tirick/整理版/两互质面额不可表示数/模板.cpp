#include <bits/stdc++.h>
using namespace std;
#define int long long

// 两互质面额不可表示数：两个互质正面额的非负整数线性组合，最大不可表示数ab-a-b，不可表示正整数个数(a-1)(b-1)/2。
// 算式O(1)，断言gcd检查O(log min(a,b))；O(1)空间。
struct Frobenius {
    int maximum(int a, int b) {
        assert(a > 0 && b > 0 && std::gcd(a, b) == 1);
        __int128 z = (__int128)a * b - a - b;
        assert(z <= LLONG_MAX);
        return z;
    }
    int count(int a, int b) {
        assert(a > 0 && b > 0 && std::gcd(a, b) == 1);
        __int128 z = (__int128)(a - 1) * (b - 1) / 2;
        assert(z <= LLONG_MAX);
        return z;
    }
};

void solve() {
    int a, b;
    cin >> a >> b;
    Frobenius t;
    cout << t.maximum(a, b) << '\n';
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

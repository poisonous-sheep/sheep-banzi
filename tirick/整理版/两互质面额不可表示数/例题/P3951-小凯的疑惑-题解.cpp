// P3951 https://www.luogu.com.cn/problem/P3951
#include <bits/stdc++.h>
using namespace std;
#define int long long

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

void init_model() {
}

void solve() {
    int a, b;
    cin >> a >> b;
    ::init_model();
    cout << ::maximum(a, b) << '\n';
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

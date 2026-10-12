// P1641 https://www.luogu.com.cn/problem/P1641
#include <bits/stdc++.h>
using namespace std;
#define int long long

// 组合依赖：本册 素数模组合数 的 Comb 定义。


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

void init_model() {
}

void solve() {
    int n, m;
    cin >> n >> m;
    ::init_model();
    cout << ::ballot(n, m, 20100403) << '\n';
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

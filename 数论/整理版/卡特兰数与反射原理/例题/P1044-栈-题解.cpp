// P1044 https://www.luogu.com.cn/problem/P1044
#include <bits/stdc++.h>
using namespace std;
#define int long long

int exact(int n) {
    assert(0 <= n && n <= 35);
    __int128 c = 1;
    for (int i = 1; i <= n; i++)
        c = c * 2 * (2 * i - 1) / (i + 1);
    return c;
}
void solve() {
    int n;
    cin >> n;
    cout << exact(n) << '\n';
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

// P1891 https://www.luogu.com.cn/problem/P1891
#include <bits/stdc++.h>
using namespace std;
#define int long long

// 组合依赖：本册 莫比乌斯反演与线性筛 的 Mobius 定义。


vector<int> f;
void init(int n) {
    Mobius t(n);
    f.assign(n + 1, 0);
    for (int d = 1; d <= n; d++)
        for (int j = d; j <= n; j += d)
            f[j] += d * t.phi[d];
}
__int128 qur(int n) {
    assert(1 <= n && n < (int)f.size());
    return (__int128)n * (f[n] + 1) / 2;
}
__int128 calc(int n) {
    vector<pair<int, int>> fac;
    int x = n;
    for (int p = 2; p <= x / p; p++)
        if (x % p == 0) {
            int e = 0;
            while (x % p == 0)
                x /= p, e++;
            fac.push_back({p, e});
        }
    if (x > 1)
        fac.push_back({x, 1});
    __int128 s = 1;
    for (auto [p, e] : fac) {
        __int128 z = 1, pow = 1;
        for (int k = 1; k <= e; k++) {
            pow *= p;
            z += pow * (pow - pow / p);
        }
        s *= z;
    }
    return (__int128)n * (s + 1) / 2;
}

void print128(__int128 x) {
    if (!x) {
        cout << 0;
        return;
    }
    string s;
    while (x)
        s.push_back('0' + x % 10), x /= 10;
    reverse(s.begin(), s.end());
    cout << s;
}

void init_model() {
}

void solve() {
    int T;
    cin >> T;
    vector<int> a(T);
    for (int &x : a)
        cin >> x;
    ::init_model();
    ::init(*max_element(a.begin(), a.end()));
    for (int x : a) {
        print128(::qur(x));
        cout << '\n';
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

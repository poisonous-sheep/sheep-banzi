// ABC109C https://atcoder.jp/contests/abc109/tasks/abc109_c
#include <bits/stdc++.h>
using namespace std;
#define int long long

int from(const vector<int> &a, int x) {
    int g = 0;
    for (int y : a)
        g = std::gcd(g, llabs(y - x));
    return g;
}

void init_model() {
}

void solve() {
    int n, x;
    cin >> n >> x;
    vector<int> a(n);
    for (int &y : a)
        cin >> y;
    ::init_model();
    cout << ::from(a, x) << '\n';
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

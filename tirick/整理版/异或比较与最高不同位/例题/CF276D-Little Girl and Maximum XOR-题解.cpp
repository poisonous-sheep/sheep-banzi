// CF276D https://codeforces.com/problemset/problem/276/D
#include <bits/stdc++.h>
using namespace std;
#define int long long

int max_xor(int l, int r) {
    assert(0 <= l && l <= r);
    int x = l ^ r, ans = 0;
    while (x) {
        ans = (ans << 1) | 1;
        x >>= 1;
    }
    return ans;
}

void init_model() {
}

void solve() {
    int l, r;
    cin >> l >> r;
    ::init_model();
    cout << ::max_xor(l, r) << '\n';
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

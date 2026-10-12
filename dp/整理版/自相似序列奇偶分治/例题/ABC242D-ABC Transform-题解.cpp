// ABC242D https://atcoder.jp/contests/abc242/tasks/abc242_d
#include <bits/stdc++.h>
using namespace std;
#define int long long

map<pair<int, string>, int> memo;

int transform(const string &s, int t, int k) {
    if (t == 0)
        return s[k] - 'A';
    if (k == 0)
        return (s[0] - 'A' + t % 3) % 3;
    return (transform(s, t - 1, k / 2) + 1 + k % 2) % 3;
}

void init_model() {
}

void solve() {
    string s;
    int q;
    cin >> s >> q;
    ::init_model();
    while (q--) {
        int time, k;
        cin >> time >> k;
        cout << char('A' + ::transform(s, time, k - 1)) << '\n';
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

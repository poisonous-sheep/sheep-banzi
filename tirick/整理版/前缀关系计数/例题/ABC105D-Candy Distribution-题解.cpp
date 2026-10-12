// ABC105D https://atcoder.jp/contests/abc105/tasks/abc105_d
#include <bits/stdc++.h>
using namespace std;
#define int long long

unordered_map<int, int> cnt;
int ans = 0;
void init(int reserve_n = 0) {
    cnt.clear();
    cnt.reserve(reserve_n * 2 + 1);
    ans = 0;
}
int add(int key) {
    int old = cnt[key];
    ans += old;
    cnt[key]++;
    return old;
}

void init_model() {
}

void solve() {
    int n, m;
    cin >> n >> m;
    ::init_model();
    ::init(n + 1);
    ::add(0);
    int s = 0;
    while (n--) {
        int x;
        cin >> x;
        s = (s + x) % m;
        ::add(s);
    }
    cout << ::ans << '\n';
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

// CF1398C https://codeforces.com/problemset/problem/1398/C
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
    int T;
    cin >> T;
    while (T--) {
        int n;
        string s;
        cin >> n >> s;
        ::init_model();
        ::init(n + 1);
        ::add(0);
        int sum = 0;
        for (int i = 1; i <= n; i++) {
            sum += s[i - 1] - '0';
            ::add(sum - i);
        }
        cout << ::ans << '\n';
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

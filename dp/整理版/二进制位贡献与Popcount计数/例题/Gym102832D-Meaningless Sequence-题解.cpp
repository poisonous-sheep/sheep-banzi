// Gym102832D https://codeforces.com/gym/102832/problem/D
#include <bits/stdc++.h>
using namespace std;
#define int long long

int mod;

int weighted(string s, int c) {
    int n = s.size();
    c %= mod;
    vector<int> pw(n + 1, 1);
    for (int i = 1; i <= n; i++)
        pw[i] = pw[i - 1] * (c + 1) % mod;
    int pre = 1, ans = 0;
    for (int i = 0; i < n; i++)
        if (s[i] == '1') {
            ans = (ans + pre * pw[n - i - 1]) % mod;
            pre = pre * c % mod;
        }
    return (ans + pre) % mod;
}

void init_model(int mod_ = 1000000007) {
    mod = mod_;
}

void solve() {
    string N;
    int c;
    cin >> N >> c;
    ::init_model();
    cout << ::weighted(N, c) << '\n';
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

// ABC356D https://atcoder.jp/contests/abc356/tasks/abc356_d
#include <bits/stdc++.h>
using namespace std;
#define int long long

int mod;

int masked(int n, int mask) {
    int ans = 0;
    for (int b = 0; b <= 60; b++)
        if ((mask >> b) & 1) {
            __int128 bit = (__int128)1 << b, period = bit * 2, len = (__int128)n + 1;
            __int128 c = (len / period) * bit + max((__int128)0, len % period - bit);
            ans = (ans + c % mod) % mod;
        }
    return ans;
}

void init_model(int mod_ = 1000000007) {
    mod = mod_;
}

void solve() {
    int N, M;
    cin >> N >> M;
    ::init_model(998244353);
    cout << ::masked(N, M) << '\n';
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

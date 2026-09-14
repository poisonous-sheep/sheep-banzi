#include <bits/stdc++.h>

using namespace std;

#define int long long
using pii = array<int, 2>;
const int mod = 1e9 + 7;
const int N = 4e6 + 10;
const int INF = 1e17;
using ll = long long;

int qpow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) res = (res * a) % mod;
        a = (a * a) % mod;
        b >>= 1;
    }
    return res;
}

int t[N][2], cnt[N][2];
ll tot = 0;

void update(ll x) {
    int u = 0;
    for (int i = 32; i >= 0; i--) {
        int ch = ((x >> i) & 1);
        if (!t[u][ch]) t[u][ch] = ++tot;
        cnt[u][ch]++;
        u = t[u][ch];
    }
}

void eras(ll x) {
    int u = 0;
    for (int i = 32; i >= 0; i--) {
        int ch = (x >> i) & 1;
        if (!t[u][ch] || cnt[u][ch] == 0) return;
        cnt[u][ch]--;
        u = t[u][ch];
    }
}

ll qur(ll x) {
    ll res = 0, u = 0;
    for (int i = 32; i >= 0; i--) {
        int ch = (x >> i) & 1;
        int to = ch ^ 1;
        if (t[u][to] && cnt[u][to] > 0) {
            res |= (1ll << i);
            u = t[u][to];
        } else if (t[u][ch] && cnt[u][ch] > 0)
            u = t[u][ch];
        else break;
    }
    return res;
}

void solve() {
    int n;
    cin >> n;
    update(0);
    while (n--) {
        char op;
        int val;
        cin >> op >> val;
        if (op == '+') update(val);
        else if (op == '-')
            eras(val);
        else cout<<qur(val)<<endl;
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t = 1;
    // cin >> t;
    while (t--) solve();
    return 0;
}

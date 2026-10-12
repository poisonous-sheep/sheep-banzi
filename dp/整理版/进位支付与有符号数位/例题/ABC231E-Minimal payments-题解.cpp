// ABC231E https://atcoder.jp/contests/abc231/tasks/abc231_e
#include <bits/stdc++.h>
using namespace std;
#define int long long

vector<int> a;
map<pair<int, int>, int> memo;
int dfs(int i, int x) {
    if (i + 1 == (int)a.size())
        return x;
    auto key = make_pair(i, x);
    if (memo.count(key))
        return memo[key];
    int base = a[i + 1] / a[i], r = x % base, q = x / base;
    int ans = r + dfs(i + 1, q);
    if (r)
        ans = min(ans, base - r + dfs(i + 1, q + 1));
    return memo[key] = ans;
}
int qur(const vector<int> &coins, int x) {
    a = coins;
    assert(!a.empty() && a[0] == 1);
    for (int i = 1; i < (int)a.size(); i++)
        assert(a[i] > a[i - 1] && a[i] % a[i - 1] == 0);
    memo.clear();
    return dfs(0, x);
}

void init_model() {
}

void solve() {
    int n, X;
    cin >> n >> X;
    vector<int> a(n);
    for (int &x : a)
        cin >> x;
    ::init_model();
    cout << ::qur(a, X) << '\n';
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

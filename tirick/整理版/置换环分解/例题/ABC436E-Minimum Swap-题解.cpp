// ABC436E https://atcoder.jp/contests/abc436/tasks/abc436_e
#include <bits/stdc++.h>
using namespace std;
#define int long long

int n;
vector<int> a, pos;
vector<vector<int>> cycle;
void init(vector<int> p) {
    a = p;
    n = a.size() - 1;
    pos.assign(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        assert(1 <= a[i] && a[i] <= n && !pos[a[i]]);
        pos[a[i]] = i;
    }
}
void build() {
    cycle.clear();
    vector<int> vis(n + 1);
    for (int u = 1; u <= n; u++)
        if (!vis[u]) {
            vector<int> c;
            int v = u;
            while (!vis[v]) {
                vis[v] = 1;
                c.push_back(v);
                v = a[v];
            }
            cycle.push_back(c);
        }
}
int min_swaps() {
    build();
    return n - cycle.size();
}
vector<pair<int, int>> sort_swaps() {
    vector<pair<int, int>> ans;
    for (int i = 1; i <= n; i++)
        if (a[i] != i) {
            int j = pos[i];
            ans.push_back({i, j});
            swap(a[i], a[j]);
            pos[a[i]] = i;
            pos[a[j]] = j;
        }
    return ans;
}
int cover_ways(int mod = 998244353) {
    build();
    vector<int> f(n + 2);
    f[1] = 1;
    for (int i = 2; i <= n + 1; i++)
        f[i] = (f[i - 1] + f[i - 2]) % mod;
    int ans = 1;
    for (auto &c : cycle) {
        int L = c.size();
        int ways = L == 1 ? 1 : (f[L - 1] + f[L + 1]) % mod;
        ans = ans * ways % mod;
    }
    return ans;
}

void init_model() {
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    ::init_model();
    ::init(a);
    ::build();
    int ans = 0;
    for (auto &c : ::cycle) {
        int L = c.size();
        ans += L * (L - 1) / 2;
    }
    cout << ans << '\n';
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

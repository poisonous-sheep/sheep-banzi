// CF161D https://codeforces.com/contest/161/problem/D
#include <bits/stdc++.h>
using namespace std;
#define int long long

int n, mod = 1000000007;
vector<vector<int>> g;

void init(int n_) {
    n = n_;
    g.assign(n + 1, {});
}
void add_edge(int u, int v) {
    g[u].push_back(v);
    g[v].push_back(u);
}

int pairs(int K) {
    vector<vector<int32_t>> f(n + 1, vector<int32_t>(K + 1));
    int ans = 0;
    function<void(int, int)> work = [&](int u, int p) {
        f[u][0] = 1;
        for (int v : g[u])
            if (v != p) {
                work(v, u);
                for (int d = 0; d < K; d++)
                    ans += (int)f[u][d] * f[v][K - d - 1];
                for (int d = 1; d <= K; d++)
                    f[u][d] += f[v][d - 1];
            }
    };
    work(1, 0);
    return ans;
}

void init_model(int n = 0) {
    init(n);
}

void solve() {
    int n, K;
    cin >> n >> K;
    ::init_model(n);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        ::add_edge(u, v);
    }
    cout << ::pairs(K) << '\n';
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

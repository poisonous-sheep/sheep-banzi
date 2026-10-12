// Gym103470H https://codeforces.com/gym/103470/problem/H
#include <bits/stdc++.h>
using namespace std;
#define int long long

int n;
vector<vector<int>> e;
vector<int> a, t, f, g, h;

void init(int n_) {
    n = n_;
    e.assign(n + 1, {});
    a.assign(n + 1, 0);
    t = a;
    f = a;
    g = a;
    h = a;
}
void add_edge(int u, int v) {
    e[u].push_back(v);
    e[v].push_back(u);
}
void dfs(int u, int fa) {
    int sum = 0, best = 0;
    pair<int, int> mx1 = {-1, 0}, mx2 = {-1, 0};
    for (int v : e[u])
        if (v != fa) {
            dfs(v, u);
            sum += f[v];
            best = max(best, a[v]);
            if (t[v] == 3) {
                pair<int, int> z = {a[v], v};
                if (z > mx1) {
                    mx2 = mx1;
                    mx1 = z;
                } else if (z > mx2)
                    mx2 = z;
            }
        }
    h[u] = a[u] + sum;
    f[u] = sum + best;
    for (int v : e[u])
        if (v != fa) {
            int other = (mx1.second == v ? mx2.first : mx1.first);
            if (other >= 0)
                f[u] = max(f[u], sum + h[v] - f[v] + other);
        }
    g[u] = f[u] + a[u];
}
int run(int root = 1) {
    dfs(root, 0);
    return g[root];
}

void init_model(int n = 0) {
    init(n);
}

void solve() {
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        ::init_model(n);
        for (int u = 1; u <= n; u++)
            cin >> ::a[u];
        for (int u = 1; u <= n; u++)
            cin >> ::t[u];
        for (int i = 1; i < n; i++) {
            int u, v;
            cin >> u >> v;
            ::add_edge(u, v);
        }
        cout << ::run() << '\n';
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

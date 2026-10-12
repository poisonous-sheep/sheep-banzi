// CF1324F https://codeforces.com/contest/1324/problem/F
#include <bits/stdc++.h>
using namespace std;
#define int long long

int n;
vector<vector<int>> son;
vector<int> a, f, ans;

void init(int n_) {
    n = n_;
    son.assign(n + 1, {});
    a.assign(n + 1, 0);
    f = ans = a;
}
void add_edge(int u, int v) {
    son[u].push_back(v);
    son[v].push_back(u);
}
void dfs(int u, int p) {
    f[u] = a[u];
    for (int v : son[u])
        if (v != p) {
            dfs(v, u);
            f[u] += max(0LL, f[v]);
        }
}
void dfs2(int u, int p, int up) {
    ans[u] = f[u] + max(0LL, up);
    for (int v : son[u])
        if (v != p)
            dfs2(v, u, ans[u] - max(0LL, f[v]));
}
void run(int root = 1) {
    dfs(root, 0);
    dfs2(root, 0, 0);
}

void init_model(int n = 0) {
    init(n);
}

void solve() {
    int n;
    cin >> n;
    ::init_model(n);
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        ::a[i] = 2 * x - 1;
    }
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        ::add_edge(u, v);
    }
    ::run();
    for (int i = 1; i <= n; i++)
        cout << ::ans[i] << " \n"[i == n];
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

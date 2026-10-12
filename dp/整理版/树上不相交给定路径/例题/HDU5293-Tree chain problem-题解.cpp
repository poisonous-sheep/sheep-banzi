// HDU5293 https://acm.hdu.edu.cn/showproblem.php?pid=5293
#include <bits/stdc++.h>
using namespace std;
#define int long long

struct info {
    int x, y, w;
};
int n, lg, timer;
vector<vector<int>> e;
vector<vector<info>> path;
vector<int> fa, dep, l, r, dp, sdp, bit;
vector<vector<int32_t>> up;

void init(int n_) {
    n = n_;
    lg = 1;
    while ((1LL << lg) <= n)
        lg++;
    timer = 0;
    e.assign(n + 1, {});
    path.assign(n + 1, {});
    fa.assign(n + 1, 0);
    dep = fa;
    l = fa;
    r = fa;
    dp = fa;
    sdp = fa;
    bit.assign(n + 2, 0);
    up.assign(lg, vector<int32_t>(n + 1));
}
void add_edge(int u, int v) {
    e[u].push_back(v);
    e[v].push_back(u);
}
void build(int u, int p) {
    fa[u] = p;
    dep[u] = dep[p] + 1;
    l[u] = ++timer;
    up[0][u] = p;
    for (int k = 1; k < lg; k++)
        up[k][u] = up[k - 1][up[k - 1][u]];
    for (int v : e[u])
        if (v != p)
            build(v, u);
    r[u] = timer;
}
void build(int root = 1) {
    timer = 0;
    build(root, 0);
}
int lca(int x, int y) {
    if (dep[x] < dep[y])
        swap(x, y);
    int d = dep[x] - dep[y];
    for (int k = 0; k < lg; k++)
        if (d >> k & 1)
            x = up[k][x];
    if (x == y)
        return x;
    for (int k = lg - 1; k >= 0; k--)
        if (up[k][x] != up[k][y]) {
            x = up[k][x];
            y = up[k][y];
        }
    return fa[x];
}
void add_path(int x, int y, int w) {
    path[lca(x, y)].push_back({x, y, w});
}
void change(int x, int v) {
    for (; x <= n + 1; x += x & -x)
        bit[x] += v;
}
int qur(int x) {
    int ans = 0;
    for (; x; x -= x & -x)
        ans += bit[x];
    return ans;
}
void dfs(int u, bool fast) {
    sdp[u] = 0;
    for (int v : e[u])
        if (v != fa[u]) {
            dfs(v, fast);
            sdp[u] += dp[v];
        }
    dp[u] = sdp[u];
    for (auto p : path[u]) {
        int tmp = sdp[u] + p.w;
        if (fast)
            tmp += qur(l[p.x]) + qur(l[p.y]);
        else {
            int x = p.x, y = p.y;
            while (x != u) {
                tmp += sdp[x] - dp[x];
                x = fa[x];
            }
            while (y != u) {
                tmp += sdp[y] - dp[y];
                y = fa[y];
            }
        }
        dp[u] = max(dp[u], tmp);
    }
    if (fast) {
        int delta = sdp[u] - dp[u];
        change(l[u], delta);
        change(r[u] + 1, -delta);
    }
}
int run(int root = 1, bool fast = true) {
    fill(bit.begin(), bit.end(), 0);
    dfs(root, fast);
    return dp[root];
}

void init_model(int n = 0) {
    init(n);
}

void solve() {
    int T;
    cin >> T;
    while (T--) {
        int n, m;
        cin >> n >> m;
        ::init_model(n);
        for (int i = 1; i < n; i++) {
            int u, v;
            cin >> u >> v;
            ::add_edge(u, v);
        }
        ::build();
        while (m--) {
            int x, y, w;
            cin >> x >> y >> w;
            ::add_path(x, y, w);
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

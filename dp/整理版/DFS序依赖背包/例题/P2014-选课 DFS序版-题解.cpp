// P2014 https://www.luogu.com.cn/problem/P2014
#include <bits/stdc++.h>
using namespace std;
#define int long long

static constexpr int INF = 4000000000000000000LL;
int n, M, tot;
vector<vector<int>> son;
vector<int> id, r, w, a;
vector<vector<int>> dp;

void init(int n_, int m) {
    n = n_;
    M = m;
    tot = 0;
    son.assign(n + 1, {});
    id.assign(n + 2, 0);
    r = w = a = id;
    dp.clear();
}
void add_edge(int u, int v) {
    son[u].push_back(v);
}
void dfs(int u) {
    id[++tot] = u;
    for (int v : son[u])
        dfs(v);
    r[u] = tot + 1;
}
int run(int root, bool exact = false) {
    tot = 0;
    dfs(root);
    dp.assign(tot + 2, vector<int>(M + 1, exact ? -INF : 0));
    dp[tot + 1][0] = 0;
    for (int i = tot; i >= 1; i--) {
        int u = id[i];
        for (int j = 0; j <= M; j++) {
            dp[i][j] = dp[r[u]][j];
            if (j >= w[u] && dp[i + 1][j - w[u]] > -INF)
                dp[i][j] = max(dp[i][j], dp[i + 1][j - w[u]] + a[u]);
        }
    }
    return dp[1][M];
}

void init_model(int n = 0, int M = 0) {
    init(n, M);
}

void solve() {
    int n, m;
    cin >> n >> m;
    ::init_model(n, m);
    for (int i = 1; i <= n; i++) {
        int p;
        cin >> p >> ::a[i];
        ::w[i] = 1;
        ::add_edge(p, i);
    }
    cout << ::run(0, true) << '\n';
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

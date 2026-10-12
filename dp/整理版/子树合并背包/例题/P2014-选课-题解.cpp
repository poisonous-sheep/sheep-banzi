// P2014 https://www.luogu.com.cn/problem/P2014
#include <bits/stdc++.h>
using namespace std;
#define int long long

static constexpr int INF = 4000000000000000000LL;
int n, M;
vector<vector<pair<int, int>>> son;
vector<int> a, w;
vector<vector<int>> dp;

void init(int n_, int m) {
    n = n_;
    M = m;
    son.assign(n + 1, {});
    a.assign(n + 1, 0);
    w.assign(n + 1, 1);
    dp.assign(n + 1, {});
}
void add_edge(int u, int v, int cost = 0) {
    son[u].push_back({v, cost});
}
void dfs(int u) {
    dp[u].assign(min(M, w[u]) + 1, -INF);
    if (w[u] <= M)
        dp[u][w[u]] = a[u];
    for (auto [v, cost] : son[u]) {
        dfs(v);
        int A = dp[u].size() - 1, B = dp[v].size() - 1;
        vector<int> tmp(min(M, A + B) + 1, -INF);
        for (int i = 0; i <= A; i++)
            if (dp[u][i] > -INF) {
                tmp[i] = max(tmp[i], dp[u][i]);
                for (int j = 1; j <= B && i + j <= M; j++)
                    if (dp[v][j] > -INF)
                        tmp[i + j] = max(tmp[i + j], dp[u][i] + dp[v][j] - cost);
            }
        dp[u].swap(tmp);
    }
    dp[u][0] = max(dp[u][0], 0LL);
}
void run(int root) {
    dfs(root);
}
int qur(int u, int k) {
    return k < (int)dp[u].size() ? dp[u][k] : -INF;
}

void init_model(int n = 0, int M = 0) {
    init(n, M);
}

void solve() {
    int n, m;
    cin >> n >> m;
    ::init_model(n, m);
    ::w[0] = 0;
    for (int i = 1; i <= n; i++) {
        int p;
        cin >> p >> ::a[i];
        ::add_edge(p, i);
    }
    ::run(0);
    cout << ::qur(0, m) << '\n';
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

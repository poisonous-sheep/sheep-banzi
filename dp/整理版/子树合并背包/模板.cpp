#include <bits/stdc++.h>
using namespace std;
#define int long long

// 子树合并背包：孩子背包卷积合并，固定点数连通选点；用户计数变体可把内部节点权重置0并扣启用边费用。
// 单位点数或叶子计数模型，限制循环到实际子树规模，总O(nM)，完整M=n时O(n²)；空间O(nM)。
struct TreeKnapsack {
    static constexpr int INF = 4000000000000000000LL;
    int n, M;
    vector<vector<pair<int, int>>> son;
    vector<int> a, w;
    vector<vector<int>> dp;
    TreeKnapsack(int n = 0, int M = 0) {
        init(n, M);
    }
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
};

void solve() {
    int n, m;
    cin >> n >> m;
    TreeKnapsack t(n, m);
    t.w[0] = 0;
    for (int i = 1; i <= n; i++) {
        int p;
        cin >> p >> t.a[i];
        t.add_edge(p, i);
    }
    t.run(0);
    cout << t.qur(0, m) << '\n';
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

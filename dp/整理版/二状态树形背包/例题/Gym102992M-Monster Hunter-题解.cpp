// Gym102992M https://codeforces.com/gym/102992/problem/M
#include <bits/stdc++.h>
using namespace std;
#define int long long

static constexpr int INF = 4000000000000000000LL;
int n;
vector<vector<int>> son;
vector<array<int, 2>> cost;
vector<array<array<int, 2>, 2>> edge_cost;
vector<vector<array<int, 2>>> dp;

void init(int n_) {
    n = n_;
    son.assign(n + 1, {});
    cost.assign(n + 1, {0, 0});
    edge_cost.resize(n + 1);
    for (auto &a : edge_cost)
        for (auto &b : a)
            b = {0, 0};
    dp.assign(n + 1, {});
}
void add_edge(int u, int v) {
    son[u].push_back(v);
}
void dfs(int u) {
    dp[u] = {{cost[u][0], INF}, {INF, cost[u][1]}};
    for (int v : son[u]) {
        dfs(v);
        int A = dp[u].size() - 1, B = dp[v].size() - 1;
        vector<array<int, 2>> tmp(A + B + 1, {INF, INF});
        for (int i = 0; i <= A; i++)
            for (int j = 0; j <= B; j++)
                for (int a = 0; a < 2; a++)
                    for (int b = 0; b < 2; b++)
                        if (dp[u][i][a] < INF && dp[v][j][b] < INF &&
                            edge_cost[v][a][b] < INF)
                            tmp[i + j][a] =
                                min(tmp[i + j][a],
                                    dp[u][i][a] + dp[v][j][b] + edge_cost[v][a][b]);
        dp[u].swap(tmp);
    }
}
vector<int> run(int root = 1) {
    dfs(root);
    vector<int> ans(n + 1, INF);
    for (int k = 0; k < (int)dp[root].size(); k++)
        ans[k] = min(dp[root][k][0], dp[root][k][1]);
    return ans;
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
        for (int i = 2; i <= n; i++) {
            int p;
            cin >> p;
            ::add_edge(p, i);
        }
        for (int i = 1; i <= n; i++) {
            int hp;
            cin >> hp;
            ::cost[i] = {hp, 0};
            ::edge_cost[i][0][0] = hp;
        }
        auto ans = ::run();
        for (int k = 0; k <= n; k++)
            cout << ans[k] << " \n"[k == n];
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

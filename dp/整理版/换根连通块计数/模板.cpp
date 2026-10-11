#include <bits/stdc++.h>
using namespace std;
#define int long long

// 换根连通块计数：计算每点被包含的连通点集数量；前后缀乘积移除一个孩子，支持非素数模。
// O(n)时间与空间，mod<=1e9+7。
struct RerootCount {
    int n, mod;
    vector<vector<int>> son;
    vector<int> dp, pd, ans;
    RerootCount(int n = 0, int m = 1000000007) {
        init(n, m);
    }
    void init(int n_, int m) {
        n = n_;
        mod = m;
        son.assign(n + 1, {});
        dp.assign(n + 1, 0);
        pd = ans = dp;
    }
    void add_edge(int u, int v) {
        son[u].push_back(v);
        son[v].push_back(u);
    }
    void dfs(int u, int p) {
        dp[u] = 1 % mod;
        for (int v : son[u])
            if (v != p) {
                dfs(v, u);
                dp[u] = dp[u] * (dp[v] + 1) % mod;
            }
    }
    void dfs2(int u, int p) {
        vector<int> a;
        for (int v : son[u])
            if (v != p)
                a.push_back(v);
        int m = a.size();
        vector<int> pre(m + 1, 1 % mod), suf(m + 1, 1 % mod);
        for (int i = 0; i < m; i++)
            pre[i + 1] = pre[i] * (dp[a[i]] + 1) % mod;
        for (int i = m - 1; i >= 0; i--)
            suf[i] = suf[i + 1] * (dp[a[i]] + 1) % mod;
        ans[u] = dp[u] * (pd[u] + 1) % mod;
        for (int i = 0; i < m; i++) {
            int v = a[i];
            pd[v] = pre[i] * suf[i + 1] % mod * (pd[u] + 1) % mod;
            dfs2(v, u);
        }
    }
    void run(int root = 1) {
        dfs(root, 0);
        pd[root] = 0;
        dfs2(root, 0);
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    RerootCount t(n, m);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        t.add_edge(u, v);
    }
    t.run();
    for (int i = 1; i <= n; i++)
        cout << t.ans[i] << '\n';
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

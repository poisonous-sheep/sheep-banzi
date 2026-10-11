#include <bits/stdc++.h>
using namespace std;
#define int long long

// 树上最大连通块权和：含根的最优连通块权和为自身加所有正的子树贡献；二次DFS给每点换根答案。
// O(n)时间与空间。
struct TreeMaxSum {
    int n;
    vector<vector<int>> son;
    vector<int> a, f, ans;
    TreeMaxSum(int n = 0) {
        init(n);
    }
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
};

void solve() {
    int n;
    cin >> n;
    TreeMaxSum t(n);
    for (int i = 1; i <= n; i++)
        cin >> t.a[i];
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        t.add_edge(u, v);
    }
    t.run();
    cout << *max_element(t.f.begin() + 1, t.f.end()) << '\n';
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

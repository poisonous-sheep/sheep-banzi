#include <bits/stdc++.h>
using namespace std;
#define int long long

// DFS增广路匹配：保留原逐左点DFS增广写法；接口与HK统一，便于比较两种算法。
// O(V_left*E)时间、O(V+E)空间。
struct HK {
    int n1, n2;
    vector<vector<int>> adj;
    vector<int> ml, mr, vis;
    void init(int n, int m) {
        n1 = n;
        n2 = m;
        adj.assign(n + 1, {});
        ml.assign(n + 1, 0);
        mr.assign(m + 1, 0);
        vis.assign(m + 1, 0);
    }
    void add(int u, int v) {
        adj[u].push_back(v);
    }
    bool dfs(int x) {
        for (int v : adj[x]) {
            if (vis[v])
                continue;
            vis[v] = 1;
            if (!mr[v] || dfs(mr[v])) {
                ml[x] = v;
                mr[v] = x;
                return true;
            }
        }
        return false;
    }
    int matching() {
        int ans = 0;
        for (int x = 1; x <= n1; x++)
            if (ml[x])
                ans++;
        for (int x = 1; x <= n1; x++)
            if (!ml[x]) {
                fill(vis.begin(), vis.end(), 0);
                if (dfs(x))
                    ans++;
            }
        return ans;
    }
};

void solve() {
    int n, m, q;
    cin >> n >> m >> q;
    HK hk;
    hk.init(n, m);
    while (q--) {
        int u, v;
        cin >> u >> v;
        hk.add(u, v);
    }
    cout << hk.matching() << '\n';
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

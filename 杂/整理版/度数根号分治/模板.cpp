#include <bits/stdc++.h>
using namespace std;
#define int long long

// 度数根号分治：小度点广播直接修改邻居，大度点广播记录时间戳；查询从相邻大点恢复最后一次颜色。
// 预处理O(n+m)，每次O(B+m/B)，B约sqrt(m)；空间O(n+m)。
struct DegreeDivide {
    int n, stamp = 0, B;
    vector<vector<int>> g, heavy;
    vector<int> big, col, tim, lazy, ltim;
    DegreeDivide(int n = 0) {
        init(n);
    }
    void init(int n_) {
        n = n_;
        stamp = 0;
        g.assign(n + 1, {});
        heavy = g;
        big.assign(n + 1, 0);
        col = tim = lazy = ltim = big;
    }
    void add_edge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }
    void build(const vector<int> &a) {
        col = a;
        int m = 0;
        for (int i = 1; i <= n; i++)
            m += g[i].size();
        B = sqrt(max(1LL, m)) + 1;
        for (int i = 1; i <= n; i++)
            big[i] = (int)g[i].size() >= B;
        for (int i = 1; i <= n; i++)
            for (int v : g[i])
                if (big[v])
                    heavy[i].push_back(v);
    }
    int qur(int u) {
        for (int v : heavy[u])
            if (ltim[v] > tim[u])
                col[u] = lazy[v], tim[u] = ltim[v];
        return col[u];
    }
    void change(int u, int c, bool self = false) {
        ++stamp;
        if (self)
            col[u] = c, tim[u] = stamp;
        if (big[u])
            lazy[u] = c, ltim[u] = stamp;
        else
            for (int v : g[u])
                col[v] = c, tim[v] = stamp;
    }
};

void solve() {
    int n, m, q;
    cin >> n >> m >> q;
    DegreeDivide t(n);
    while (m--) {
        int u, v;
        cin >> u >> v;
        t.add_edge(u, v);
    }
    vector<int> a(n + 1);
    iota(a.begin(), a.end(), 0);
    t.build(a);
    while (q--) {
        int x;
        cin >> x;
        int c = t.qur(x);
        t.change(x, c);
    }
    for (int i = 1; i <= n; i++)
        cout << t.qur(i) << " \n"[i == n];
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

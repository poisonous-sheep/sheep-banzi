#include <bits/stdc++.h>
using namespace std;
#define int long long

// 点双连通分量：Tarjan点栈构造点双；割点可属于多个块，孤立点单独成块。
// O(n+m)时间与空间。
struct VDCC {
    int n, idx;                       // n：顶点数；idx：DFS 时钟。
    vector<vector<pair<int, int>>> e; // 二维，(v,id) 为邻点和唯一无向边编号。
    vector<int> dfn, low, cut,
        stk; // 一维：dfn/low 按顶点访问；cut[u] 割点标记；stk[j] 待归块顶点。
    vector<vector<int>> bcc; // 二维，bcc[k] 存第 k 个点双的原图顶点，k 从 0 开始。

    void init(int n_) {
        n = n_;
        idx = 0;
        e.assign(n + 1, {});
        dfn.assign(n + 1, 0);
        low.assign(n + 1, 0);
        cut.assign(n + 1, 0);
        stk.clear();
        bcc.clear();
    }
    void addedge(int u, int v, int id) {
        if (u == v)
            return;
        e[u].push_back({v, id});
        e[v].push_back({u, id});
    }
    void dfs(int u, int id) {
        dfn[u] = low[u] = ++idx;
        stk.push_back(u);
        int ch = 0; // u 的 DFS 树儿子数。
        if (e[u].empty()) {
            bcc.push_back({u});
            stk.pop_back();
            return;
        }
        for (auto [v, id2] : e[u]) {
            if (id2 == id)
                continue;
            if (!dfn[v]) {
                ++ch;
                dfs(v, id2);
                low[u] = min(low[u], low[v]);
                if (low[v] >= dfn[u]) {
                    if (id != -1)
                        cut[u] = 1;
                    vector<int> c; // 一维，本次弹出的块；u 作为公共边界另行加入。
                    while (true) {
                        int x = stk.back(); // x：从点栈弹出的块内顶点。
                        stk.pop_back();
                        c.push_back(x);
                        if (x == v)
                            break;
                    }
                    c.push_back(u);
                    bcc.push_back(c);
                }
            } else
                low[u] = min(low[u], dfn[v]);
        }
        if (id == -1 && ch >= 2)
            cut[u] = 1;
    }
    void run() {
        for (int u = 1; u <= n; u++)
            if (!dfn[u]) {
                dfs(u, -1);
                stk.clear(); // 本棵 DFS 树的根可能仍留在栈中。
            }
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    VDCC g;
    g.init(n);
    for (int id = 0; id < m; id++) {
        int u, v;
        cin >> u >> v;
        g.addedge(u, v, id);
    }
    g.run();
    cout << g.bcc.size() << '\n';
    for (auto &c : g.bcc) {
        cout << c.size();
        for (int u : c)
            cout << ' ' << u;
        cout << '\n';
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

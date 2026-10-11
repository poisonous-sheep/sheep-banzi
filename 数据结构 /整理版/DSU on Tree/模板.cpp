#include <bits/stdc++.h>
using namespace std;
#define int long long

// DSU on Tree：轻子树算完清空、重子树保留，以单一统计容器回答所有子树询问。
// O(n log n)次增删；总时间再乘增删与询问成本；O(n)树结构空间。
struct DSUOnTree {
    int n, tot = 0;
    vector<vector<int>> adj;
    vector<int> fa, siz, son, l, r, seq;
    DSUOnTree(int n = 0) {
        init(n);
    }
    void init(int n_) {
        n = n_;
        tot = 0;
        adj.assign(n + 1, {});
        fa.assign(n + 1, 0);
        siz = son = l = r = fa;
        seq.assign(n + 1, 0);
    }
    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void dfs1(int u, int p) {
        fa[u] = p;
        siz[u] = 1;
        l[u] = ++tot;
        seq[tot] = u;
        for (int v : adj[u])
            if (v != p) {
                dfs1(v, u);
                siz[u] += siz[v];
                if (siz[v] > siz[son[u]])
                    son[u] = v;
            }
        r[u] = tot;
    }
    template <class Change, class Answer>
    void dfs2(int u, bool keep, Change &change, Answer &answer) {
        for (int v : adj[u])
            if (v != fa[u] && v != son[u])
                dfs2(v, false, change, answer);
        if (son[u])
            dfs2(son[u], true, change, answer);
        for (int v : adj[u])
            if (v != fa[u] && v != son[u])
                for (int i = l[v]; i <= r[v]; i++)
                    change(seq[i], 1);
        change(u, 1);
        answer(u);
        if (!keep)
            for (int i = l[u]; i <= r[u]; i++)
                change(seq[i], -1);
    }
    template <class Change, class Answer>
    void run(Change change, Answer answer, int root = 1) {
        tot = 0;
        fill(son.begin(), son.end(), 0);
        dfs1(root, 0);
        dfs2(root, false, change, answer);
    }
};

void solve() {
    int n;
    cin >> n;
    vector<int> c(n + 1), ans(n + 1), cnt(n + 1), fc(n + 1), sum(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> c[i];
    DSUOnTree t(n);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        t.add_edge(u, v);
    }
    int mx = 0;
    auto change = [&](int u, int d) {
        int x = c[u], k = cnt[x];
        if (k)
            fc[k]--, sum[k] -= x;
        k = cnt[x] += d;
        if (k)
            fc[k]++, sum[k] += x;
        mx = max(mx, k);
        while (mx && !fc[mx])
            mx--;
    };
    auto answer = [&](int u) { ans[u] = sum[mx]; };
    t.run(change, answer);
    for (int i = 1; i <= n; i++)
        cout << ans[i] << " \n"[i == n];
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

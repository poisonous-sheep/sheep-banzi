#include <bits/stdc++.h>

using namespace std;

#define int long long
#define endl '\n'

using pii = pair<int, int>;

const int INF = 4e18;

struct SegGraph {
    int n;
    int tot;

    // out：点 -> 区间，父 -> 子
    // in ：区间 -> 点，子 -> 父
    vector<int> out, in;

    struct edge {
        int to, w;
    };

    vector<vector<edge>> adj;

    inline int ls(int id) { return id << 1; }

    inline int rs(int id) { return id << 1 | 1; }

    SegGraph(int _n) {
        n = _n;
        tot = n;

        out.resize(4 * n + 10);
        in.resize(4 * n + 10);

        // 总节点约 3n
        adj.resize(4 * n + 10);

        build_out(1, 1, n);
        build_in(1, 1, n);
    }

    // 普通建边
    void add_edge(int u, int v, int w) { adj[u].push_back({v, w}); }

    /*
        点 -> 区间

        out 树：

              父
             /  \
            ↓    ↓
           左    右
    */
    void build_out(int id, int l, int r) {
        if (l == r) {
            out[id] = l;
            return;
        }

        out[id] = ++tot;

        int mid = (l + r) >> 1;

        build_out(ls(id), l, mid);
        build_out(rs(id), mid + 1, r);

        add_edge(out[id], out[ls(id)], 0);
        add_edge(out[id], out[rs(id)], 0);
    }

    /*
        区间 -> 点

        in 树：

           左    右
            ↓    ↓
              父
    */
    void build_in(int id, int l, int r) {
        if (l == r) {
            in[id] = l;
            return;
        }

        in[id] = ++tot;

        int mid = (l + r) >> 1;

        build_in(ls(id), l, mid);
        build_in(rs(id), mid + 1, r);

        add_edge(in[ls(id)], in[id], 0);
        add_edge(in[rs(id)], in[id], 0);
    }

    /*
        v -> [ql, qr]
    */
    void add_out(int id, int l, int r, int ql, int qr, int v, int w) {
        if (ql <= l && r <= qr) {
            add_edge(v, out[id], w);
            return;
        }

        int mid = (l + r) >> 1;

        if (ql <= mid) add_out(ls(id), l, mid, ql, qr, v, w);

        if (qr > mid) add_out(rs(id), mid + 1, r, ql, qr, v, w);
    }

    // 外部调用版本
    void add_out(int v, int l, int r, int w) { add_out(1, 1, n, l, r, v, w); }

    /*
        [ql, qr] -> v
    */
    void add_in(int id, int l, int r, int ql, int qr, int v, int w) {
        if (ql <= l && r <= qr) {
            add_edge(in[id], v, w);
            return;
        }

        int mid = (l + r) >> 1;

        if (ql <= mid) add_in(ls(id), l, mid, ql, qr, v, w);

        if (qr > mid) add_in(rs(id), mid + 1, r, ql, qr, v, w);
    }

    // 外部调用版本
    void add_in(int l, int r, int v, int w) { add_in(1, 1, n, l, r, v, w); }

    /*
        Dijkstra
    */
    vector<int> dijkstra(int s) {
        vector<int> dis(tot + 1, INF);
        vector<bool> vis(tot + 1);

        priority_queue<pii, vector<pii>, greater<pii>> pq;

        dis[s] = 0;
        pq.push({0, s});

        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();

            if (vis[u]) continue;
            vis[u] = true;

            for (auto [v, w] : adj[u]) {
                if (dis[v] > d + w) {
                    dis[v] = d + w;
                    pq.push({dis[v], v});
                }
            }
        }

        return dis;
    }
};

void solve() {
    int n, q, s;
    cin >> n >> q >> s;
    SegGraph sg(n);
    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int v, u, w;
            cin >> v >> u >> w;
            // 点 -> 点
            sg.add_edge(v, u, w);
        }
        else if (op == 2) {
            int v, l, r, w;
            cin >> v >> l >> r >> w;

            // v -> [l, r]
            sg.add_out(v, l, r, w);
        }

        else {
            int v, l, r, w;
            cin >> v >> l >> r >> w;

            // [l, r] -> v
            sg.add_in(l, r, v, w);
        }
    }

    auto dis = sg.dijkstra(s);

    for (int i = 1; i <= n; i++) {
        if (dis[i] == INF)
            cout << -1 << " ";
        else
            cout << dis[i] << " ";
    }

    cout << endl;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}

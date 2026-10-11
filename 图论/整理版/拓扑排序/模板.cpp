#include <bits/stdc++.h>
using namespace std;
#define int long long

// 拓扑排序：Kahn拓扑序，保留原队列写法；可选最小堆得到字典序最小拓扑序。
// 队列O(n+m)，字典序O((n+m)log n)，空间O(n+m)。
struct Topo {
    int n;
    vector<vector<int>> edge;
    vector<int> d;
    void init(int n_) {
        n = n_;
        edge.assign(n + 1, {});
        d.assign(n + 1, 0);
    }
    void addedge(int u, int v) {
        edge[u].push_back(v);
        d[v]++;
    }
    vector<int> toposort(bool lex = false) {
        vector<int> deg = d, res;
        queue<int> q;
        priority_queue<int, vector<int>, greater<int>> pq;
        for (int i = 1; i <= n; i++)
            if (!deg[i]) {
                if (lex)
                    pq.push(i);
                else
                    q.push(i);
            }
        while (lex ? !pq.empty() : !q.empty()) {
            int u;
            if (lex) {
                u = pq.top();
                pq.pop();
            } else {
                u = q.front();
                q.pop();
            }
            res.push_back(u);
            for (int v : edge[u])
                if (!--deg[v]) {
                    if (lex)
                        pq.push(v);
                    else
                        q.push(v);
                }
        }
        return res;
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    Topo g;
    g.init(n);
    while (m--) {
        int u, v;
        cin >> u >> v;
        g.addedge(u, v);
    }
    vector<int> dp(n + 1, 1);
    for (int u : g.toposort())
        for (int v : g.edge[u])
            dp[v] = max(dp[v], dp[u] + 1);
    for (int i = 1; i <= n; i++)
        cout << dp[i] << '\n';
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

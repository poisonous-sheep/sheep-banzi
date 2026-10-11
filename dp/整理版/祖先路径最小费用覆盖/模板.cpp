#include <bits/stdc++.h>
using namespace std;
#define int long long

// 祖先路径最小费用覆盖：从给定非负费用祖先—后代路径中选若干条覆盖全部点，可重叠。保留最高到达深度DP，补充适合大数据的可并堆费用扣减版。
// 深度DP O(n²+m)时间/最坏O(n²)空间；可并堆O((n+m)log(m+1))时间/O(n+m)空间。
struct AncestorCover {
    struct node {
        int ls = 0, rs = 0, dist = 1, key = 0, lazy = 0, top = 0;
    };
    static constexpr int INF = 4000000000000000000LL;
    int n, answer;
    bool ok;
    vector<vector<int>> son;
    vector<vector<pair<int, int>>> path;
    vector<int> dep, rt;
    vector<vector<int>> dp;
    vector<node> tr;
    AncestorCover(int n = 0) {
        init(n);
    }
    void init(int n_) {
        n = n_;
        son.assign(n + 1, {});
        path.assign(n + 1, {});
        dep.assign(n + 1, 0);
        rt = dep;
        dp.assign(n + 1, {});
        tr.assign(1, node{});
        tr[0].dist = 0;
    }
    void add_edge(int u, int v) {
        son[u].push_back(v);
    }
    void build(int u = 1) {
        for (int v : son[u]) {
            dep[v] = dep[u] + 1;
            build(v);
        }
    }
    void add_path(int bottom, int top, int cost) {
        assert(cost >= 0);
        path[bottom].push_back({dep[top], cost});
    }
    void dfs(int u) {
        int L = dep[u] + 1;
        dp[u].assign(L + 1, INF);
        dp[u][L] = 0;
        for (auto [d, w] : path[u])
            dp[u][d] = min(dp[u][d], w);
        for (int v : son[u]) {
            dfs(v);
            vector<int> a = dp[u], b = dp[v], sa(L + 2, INF), sb(L + 2, INF);
            for (int k = L; k >= 0; k--) {
                sa[k] = min(sa[k + 1], a[k]);
                sb[k] = min(sb[k + 1], b[k]);
            }
            for (int k = 0; k <= L; k++)
                dp[u][k] = min(INF, min(a[k] + sb[k], b[k] + sa[k]));
        }
        dp[u][L] = INF; // 返回父亲前，u必须已经被覆盖。
    }
    int run(int root = 1) {
        dfs(root);
        int z = *min_element(dp[root].begin(), dp[root].end());
        return z >= INF ? -1 : z;
    }
    void apply(int p, int v) {
        if (p) {
            tr[p].key += v;
            tr[p].lazy += v;
        }
    }
    void push(int p) {
        if (tr[p].lazy) {
            apply(tr[p].ls, tr[p].lazy);
            apply(tr[p].rs, tr[p].lazy);
            tr[p].lazy = 0;
        }
    }
    int merge(int x, int y) {
        if (!x || !y)
            return x + y;
        if (tr[x].key > tr[y].key)
            swap(x, y);
        push(x);
        tr[x].rs = merge(tr[x].rs, y);
        if (tr[tr[x].ls].dist < tr[tr[x].rs].dist)
            swap(tr[x].ls, tr[x].rs);
        tr[x].dist = tr[tr[x].rs].dist + 1;
        return x;
    }
    int pop(int x) {
        push(x);
        return merge(tr[x].ls, tr[x].rs);
    }
    void dfs_heap(int u) {
        rt[u] = 0;
        for (int v : son[u]) {
            dfs_heap(v);
            rt[u] = merge(rt[u], rt[v]);
        }
        for (auto [d, w] : path[u]) {
            node a;
            a.key = w;
            a.top = d;
            tr.push_back(a);
            rt[u] = merge(rt[u], tr.size() - 1);
        }
        while (rt[u] && tr[rt[u]].top > dep[u])
            rt[u] = pop(rt[u]);
        if (!rt[u]) {
            ok = false;
            return;
        }
        int val = tr[rt[u]].key;
        answer += val;
        apply(rt[u], -val);
    }
    int run_heap(int root = 1) {
        tr.assign(1, node{});
        tr[0].dist = 0;
        answer = 0;
        ok = true;
        dfs_heap(root);
        return ok ? answer : -1;
    }
};

void solve() {
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        AncestorCover t(n);
        vector<int> fa(n + 1), used(n + 1);
        int root = 0;
        for (int u = 1; u <= n; u++) {
            cin >> fa[u];
            if (fa[u] == u)
                root = u;
            else
                t.add_edge(fa[u], u);
        }
        t.build(root);
        for (int u = 1; u <= n; u++)
            if (t.son[u].empty())
                t.add_path(u, root, 1);
        cout << t.run_heap(root) << '\n';
        for (int u = 1; u <= n; u++)
            if (t.son[u].empty()) {
                vector<int> p;
                int v = u;
                while (!used[v]) {
                    p.push_back(v);
                    used[v] = 1;
                    if (v == root)
                        break;
                    v = fa[v];
                }
                reverse(p.begin(), p.end());
                cout << p.size() << '\n';
                for (int x : p)
                    cout << x << ' ';
                cout << '\n';
            }
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

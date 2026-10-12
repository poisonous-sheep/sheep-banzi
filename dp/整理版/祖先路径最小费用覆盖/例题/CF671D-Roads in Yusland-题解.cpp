// CF671D https://codeforces.com/problemset/problem/671/D
#include <bits/stdc++.h>
using namespace std;
#define int long long

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

void init_model(int n = 0) {
    init(n);
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> e(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    ::init_model(n);
    int L = 1;
    while ((1LL << L) <= n)
        L++;
    vector<vector<int32_t>> up(L, vector<int32_t>(n + 1));
    function<void(int, int)> dfs = [&](int u, int p) {
        up[0][u] = p;
        for (int k = 1; k < L; k++)
            up[k][u] = up[k - 1][up[k - 1][u]];
        for (int v : e[u])
            if (v != p) {
                ::add_edge(u, v);
                ::dep[v] = ::dep[u] + 1;
                dfs(v, u);
            }
    };
    dfs(1, 0);
    ::add_path(1, 1, 0);
    while (m--) {
        int u, v, c;
        cin >> u >> v >> c;
        if (u == v)
            continue;
        int x = u, d = ::dep[u] - ::dep[v] - 1;
        for (int k = 0; k < L; k++)
            if (d >> k & 1)
                x = up[k][x];
        ::add_path(u, x, c);
    }
    cout << ::run_heap() << '\n';
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

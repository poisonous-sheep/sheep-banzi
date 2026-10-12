// P4381 https://www.luogu.com.cn/problem/P4381
#include <bits/stdc++.h>
using namespace std;
#define int long long

int n;
vector<int> p, w, val;
vector<int32_t> head, nxt;
vector<char> vis, on;
vector<vector<int>> cycles;

void init(int n_) {
    n = n_;
    p.assign(n + 1, 0);
    w = val = p;
    head.assign(n + 1, -1);
    nxt = head;
    vis.assign(n + 1, 0);
    on = vis;
    cycles.clear();
}
void build() {
    fill(head.begin(), head.end(), -1);
    fill(vis.begin(), vis.end(), 0);
    fill(on.begin(), on.end(), 0);
    cycles.clear();
    for (int u = 1; u <= n; u++) {
        assert(1 <= p[u] && p[u] <= n);
        nxt[u] = head[p[u]];
        head[p[u]] = u;
    }
    for (int i = 1; i <= n; i++)
        if (!vis[i]) {
            int u = i;
            while (!vis[u])
                vis[u] = 1, u = p[u];
            if (vis[u] == 1) {
                vector<int> c;
                int v = u;
                do {
                    c.push_back(v);
                    on[v] = 1;
                    v = p[v];
                } while (v != u);
                cycles.push_back(c);
            }
            u = i;
            while (vis[u] == 1)
                vis[u] = 2, u = p[u];
        }
}
void orient(const vector<array<int, 3>> &edges) {
    vector<vector<array<int, 3>>> g(n + 1);
    vector<int> deg(n + 1);
    int eid = 0;
    for (auto [u, v, c] : edges) {
        g[u].push_back({v, c, eid});
        g[v].push_back({u, c, eid++});
        deg[u]++;
        deg[v]++;
    }
    queue<int> q;
    for (int u = 1; u <= n; u++)
        if (deg[u] == 1)
            q.push(u);
    vector<char> removed(n + 1);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        removed[u] = 1;
        for (auto [v, c, id] : g[u])
            if (!removed[v]) {
                p[u] = v;
                w[u] = c;
                if (--deg[v] == 1)
                    q.push(v);
                break;
            }
    }
    vector<char> used(n + 1);
    for (int i = 1; i <= n; i++)
        if (!removed[i] && !used[i]) {
            int u = i, prev = -1;
            do {
                used[u] = 1;
                array<int, 3> z = {0, 0, -1};
                for (auto [v, c, id] : g[u])
                    if (!removed[v] && id != prev) {
                        z = {v, c, id};
                        break;
                    }
                assert(z[0]);
                p[u] = z[0];
                w[u] = z[1];
                prev = z[2];
                u = z[0];
            } while (u != i);
        }
    build();
}

vector<int> d;
int inside;

void dfs(int u) {
    d[u] = 0;
    for (int v = head[u]; v != -1; v = nxt[v])
        if (!on[v]) {
            dfs(v);
            int x = d[v] + w[v];
            inside = max(inside, d[u] + x);
            d[u] = max(d[u], x);
        }
}
int ring_path(const vector<int> &a, const vector<int> &b) {
    int k = a.size();
    if (k <= 1)
        return 0;
    vector<int> s(2 * k);
    for (int i = 1; i < 2 * k; i++)
        s[i] = s[i - 1] + b[(i - 1) % k];
    deque<int> q;
    int ans = 0;
    for (int i = 0; i < 2 * k; i++) {
        while (!q.empty() && i - q.front() >= k)
            q.pop_front();
        if (!q.empty())
            ans = max(ans, a[i % k] + s[i] + a[q.front() % k] - s[q.front()]);
        while (!q.empty() && a[q.back() % k] - s[q.back()] <= a[i % k] - s[i])
            q.pop_back();
        q.push_back(i);
    }
    return ans;
}
int run() {
    build();
    d.assign(n + 1, 0);
    int ans = 0;
    for (auto c : cycles) {
        inside = 0;
        vector<int> a, b;
        for (int u : c) {
            dfs(u);
            a.push_back(d[u]);
            b.push_back(w[u]);
        }
        ans += max(inside, ring_path(a, b));
    }
    return ans;
}
struct info {
    int minus, plus, best;
};
info merge(info a, info b) {
    return {max(a.minus, b.minus), max(a.plus, b.plus),
            max({a.best, b.best, a.minus + b.plus})};
}
int minimum_cut_diameter() {
    build();
    assert(cycles.size() == 1);
    auto c = cycles[0];
    int k = c.size();
    d.assign(n + 1, 0);
    inside = 0;
    for (int u : c)
        dfs(u);
    if (k <= 1)
        return inside;
    vector<int> s(2 * k);
    for (int i = 1; i < 2 * k; i++)
        s[i] = s[i - 1] + w[c[(i - 1) % k]];
    vector<pair<info, info>> in, out;
    auto push = [&](info z) {
        in.push_back({z, in.empty() ? z : merge(in.back().second, z)});
    };
    auto pop = [&]() {
        if (out.empty())
            while (!in.empty()) {
                info z = in.back().first;
                in.pop_back();
                out.push_back({z, out.empty() ? z : merge(z, out.back().second)});
            }
        out.pop_back();
    };
    auto qur = [&]() {
        if (in.empty())
            return out.back().second.best;
        if (out.empty())
            return in.back().second.best;
        return merge(out.back().second, in.back().second).best;
    };
    int ans = 4000000000000000000LL;
    for (int i = 0; i < 2 * k - 1; i++) {
        push({d[c[i % k]] - s[i], d[c[i % k]] + s[i], 0});
        if (i >= k)
            pop();
        if (i >= k - 1)
            ans = min(ans, max(inside, qur()));
    }
    return ans;
}

void init_model(int n = 0) {
    init(n);
}

void solve() {
    int n;
    cin >> n;
    ::init_model(n);
    for (int i = 1; i <= n; i++)
        cin >> ::p[i] >> ::w[i];
    cout << ::run() << '\n';
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

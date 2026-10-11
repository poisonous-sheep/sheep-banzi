#include <bits/stdc++.h>
using namespace std;
#define int long long

// 启发式合并：每次枚举小容器合入大容器；保留颜色桶句柄交换与map统计两个原资料模型。
// 位置桶总O(n log n+q)，map树上合并O(n log²n)；空间O(n+颜色数)。
struct SmallMerge {
    int n, segments;
    vector<int> a, id;
    vector<vector<int>> pos;
    SmallMerge(int n = 0) {
        init(n);
    }
    void init(int n_) {
        n = n_;
        a.assign(n + 2, 0);
        pos.assign(n + 1, {});
        id.clear();
        segments = 0;
    }
    void build(const vector<int> &col, int kinds) {
        id.resize(kinds + 1);
        iota(id.begin(), id.end(), 0);
        pos.resize(kinds + 1);
        for (int i = 1; i <= n; i++) {
            a[i] = col[i];
            pos[a[i]].push_back(i);
            segments += (i == 1 || a[i] != a[i - 1]);
        }
    }
    void change(int x, int y) {
        if (x == y)
            return;
        if (pos[id[x]].size() > pos[id[y]].size())
            swap(id[x], id[y]);
        int u = id[x], v = id[y];
        for (int p : pos[u]) {
            if (p > 1)
                segments -= (a[p] != a[p - 1]);
            if (p < n)
                segments -= (a[p] != a[p + 1]);
            a[p] = v;
            if (p > 1)
                segments += (a[p] != a[p - 1]);
            if (p < n)
                segments += (a[p] != a[p + 1]);
            pos[v].push_back(p);
        }
        vector<int>().swap(pos[u]);
    }
    // 另一种容器：小map并入大map，维护最大出现次数的颜色编号和。
    struct info {
        map<int, int> cnt;
        int mx = 0, sum = 0;
    };
    static void insert(info &s, int c, int k) {
        int x = (s.cnt[c] += k);
        if (x > s.mx)
            s.mx = x, s.sum = c;
        else if (x == s.mx)
            s.sum += c;
    }
    static void merge(info &a, info &b) {
        if (a.cnt.size() < b.cnt.size())
            swap(a, b);
        for (auto [c, k] : b.cnt)
            insert(a, c, k);
        b = info();
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1), all;
    for (int i = 1; i <= n; i++)
        cin >> a[i], all.push_back(a[i]);
    struct op {
        int t, x, y;
    };
    vector<op> q(m);
    for (auto &z : q) {
        cin >> z.t;
        if (z.t == 1) {
            cin >> z.x >> z.y;
            all.push_back(z.x);
            all.push_back(z.y);
        }
    }
    sort(all.begin(), all.end());
    all.erase(unique(all.begin(), all.end()), all.end());
    auto id = [&](int x) {
        return lower_bound(all.begin(), all.end(), x) - all.begin() + 1;
    };
    for (int i = 1; i <= n; i++)
        a[i] = id(a[i]);
    SmallMerge t(n);
    t.build(a, all.size());
    for (auto z : q)
        if (z.t == 1)
            t.change(id(z.x), id(z.y));
        else
            cout << t.segments << '\n';
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

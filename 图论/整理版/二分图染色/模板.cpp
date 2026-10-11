#include <bits/stdc++.h>
using namespace std;
#define int long long

// 二分图染色：判断无向图是否可二染色，并统计每个连通块的两色数量。
// O(n+m)时间与空间。
struct BipColor {
    int n;
    vector<vector<int>> e;
    vector<int> col;
    vector<array<int, 2>> cnt;
    void init(int n_) {
        n = n_;
        e.assign(n + 1, {});
        col.assign(n + 1, -1);
        cnt.clear();
    }
    void addedge(int u, int v) {
        e[u].push_back(v);
        e[v].push_back(u);
    }
    bool dfs(int u, int c, array<int, 2> &num) {
        col[u] = c;
        num[c]++;
        for (int v : e[u]) {
            if (col[v] == -1) {
                if (!dfs(v, c ^ 1, num))
                    return false;
            } else if (col[v] == c)
                return false;
        }
        return true;
    }
    bool run() {
        fill(col.begin(), col.end(), -1);
        cnt.clear();
        for (int u = 1; u <= n; u++)
            if (col[u] == -1) {
                array<int, 2> num = {0, 0};
                if (!dfs(u, 0, num))
                    return false;
                cnt.push_back(num);
            }
        return true;
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(m), b(m);
    for (int &x : a)
        cin >> x;
    for (int &x : b)
        cin >> x;
    BipColor g;
    g.init(n);
    for (int i = 0; i < m; i++)
        g.addedge(a[i], b[i]);
    cout << (g.run() ? "Yes" : "No") << '\n';
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

#include <bits/stdc++.h>
using namespace std;
#define int long long

// 并查集：动态合并连通块，查询连通性与大小；编号0..n均可用。
// 初始化O(n)，按大小合并与路径压缩均摊O(alpha(n))，空间O(n)。
struct DSU {
    vector<int> fid, sz;
    DSU(int n = 0) {
        init(n);
    }
    void init(int n) {
        fid.resize(n + 1);
        iota(fid.begin(), fid.end(), 0);
        sz.assign(n + 1, 1);
    }
    int root(int x) {
        return fid[x] == x ? x : fid[x] = root(fid[x]);
    }
    bool merge(int x, int y) {
        x = root(x);
        y = root(y);
        if (x == y)
            return false;
        if (sz[x] > sz[y])
            swap(x, y);
        fid[x] = y;
        sz[y] += sz[x];
        return true;
    }
    bool same(int x, int y) {
        return root(x) == root(y);
    }
    int size(int x) {
        return sz[root(x)];
    }
};

void solve() {
    int n, q;
    cin >> n >> q;
    DSU dsu(n);
    while (q--) {
        int op, u, v;
        cin >> op >> u >> v;
        if (!op)
            dsu.merge(u, v);
        else
            cout << dsu.same(u, v) << '\n';
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

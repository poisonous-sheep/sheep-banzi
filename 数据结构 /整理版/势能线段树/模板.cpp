#include <bits/stdc++.h>
using namespace std;
#define int long long

// 势能线段树：非负数组区间开方、区间取模、单点赋值和区间和；用mx跳过不变节点。
// 开方每值只改变O(log log A)次；取模有效改变使值至少减半，累计O((n+m)log A log n)；查询O(log n)，空间O(n)。
struct SegTree {
    struct info {
        int sum = 0, mx = 0;
        friend info operator+(const info &l, const info &r) {
            return {l.sum + r.sum, max(l.mx, r.mx)};
        }
    };
    struct node {
        info val;
    };
    int n;
    vector<node> seg;
    int ls(int id) {
        return id << 1;
    }
    int rs(int id) {
        return id << 1 | 1;
    }
    void update(int id) {
        seg[id].val = seg[ls(id)].val + seg[rs(id)].val;
    }
    void build(int id, int l, int r, const vector<int> &a) {
        if (l == r) {
            seg[id].val = {a[l], a[l]};
            return;
        }
        int mid = (l + r) >> 1;
        build(ls(id), l, mid, a);
        build(rs(id), mid + 1, r, a);
        update(id);
    }
    void build(const vector<int> &a) {
        n = a.size() - 1;
        assert(n > 0);
        seg.assign(4 * n + 4, {});
        build(1, 1, n, a);
    }
    int isqrt(int x) {
        int y = sqrtl((long double)x);
        while ((__int128)y * y > x)
            --y;
        while ((__int128)(y + 1) * (y + 1) <= x)
            ++y;
        return y;
    }
    void update_sqrt(int id, int l, int r, int ql, int qr) {
        if (qr < l || r < ql || seg[id].val.mx <= 1)
            return;
        if (l == r) {
            int v = isqrt(seg[id].val.mx);
            seg[id].val = {v, v};
            return;
        }
        int mid = (l + r) >> 1;
        update_sqrt(ls(id), l, mid, ql, qr);
        update_sqrt(rs(id), mid + 1, r, ql, qr);
        update(id);
    }
    void modify_mod(int id, int l, int r, int ql, int qr, int x) {
        if (qr < l || r < ql || seg[id].val.mx < x)
            return;
        if (l == r) {
            int v = seg[id].val.mx % x;
            seg[id].val = {v, v};
            return;
        }
        int mid = (l + r) >> 1;
        modify_mod(ls(id), l, mid, ql, qr, x);
        modify_mod(rs(id), mid + 1, r, ql, qr, x);
        update(id);
    }
    void change(int id, int l, int r, int p, int x) {
        if (l == r) {
            seg[id].val = {x, x};
            return;
        }
        int mid = (l + r) >> 1;
        if (p <= mid)
            change(ls(id), l, mid, p, x);
        else
            change(rs(id), mid + 1, r, p, x);
        update(id);
    }
    info qur(int id, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr)
            return seg[id].val;
        int mid = (l + r) >> 1;
        if (qr <= mid)
            return qur(ls(id), l, mid, ql, qr);
        if (ql > mid)
            return qur(rs(id), mid + 1, r, ql, qr);
        return qur(ls(id), l, mid, ql, qr) + qur(rs(id), mid + 1, r, ql, qr);
    }
    void update_sqrt(int l, int r) {
        update_sqrt(1, 1, n, l, r);
    }
    void modify_mod(int l, int r, int x) {
        assert(x > 0);
        modify_mod(1, 1, n, l, r, x);
    }
    void change(int p, int x) {
        assert(x >= 0);
        change(1, 1, n, p, x);
    }
    info qur(int l, int r) {
        return qur(1, 1, n, l, r);
    }
};

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    SegTree seg;
    seg.build(a);
    int m;
    cin >> m;
    while (m--) {
        int op, l, r;
        cin >> op >> l >> r;
        if (l > r)
            swap(l, r);
        if (!op)
            seg.update_sqrt(l, r);
        else
            cout << seg.qur(l, r).sum << '\n';
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
